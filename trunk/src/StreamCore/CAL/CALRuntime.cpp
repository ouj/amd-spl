#include <iostream>
#include <vector>
#include "CALBase.h"
#include "CALRuntime.h"
#include "CALDevice.h"
#include <assert.h>
#include "CALBufferMgr.h"
#include "CALProgramMgr.h"


////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Constructor
//!
////////////////////////////////////////////////////////////////////////////////
namespace amdspl
{
    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Constructor
    //!
    ////////////////////////////////////////////////////////////////////////////////

    CalRuntime::CalRuntime() :_numDevices(0)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Destructor
    //!
    ////////////////////////////////////////////////////////////////////////////////

    CalRuntime::~CalRuntime()
    {
        calShutdown();
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Function called from Runtime. It is used to construct the backend
    //! specific runtime
    //!
    ////////////////////////////////////////////////////////////////////////////////

    CalRuntime*
        CalRuntime::create()
    {
        CalRuntime* runtime = new CalRuntime();
        if(!runtime->initialize())
        {
            delete runtime;
            return NULL;
        }

        return runtime;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief initializes the Runtime.
    //!
    //! \return flag saying initialization was proper or not
    //!
    ////////////////////////////////////////////////////////////////////////////////

    bool
        CalRuntime::initialize()
    {
        CALresult result;

        // Initialize CAL
        result = calInit();
        AMDSPL_CHECK_CAL_RESULT(result, "Failed to initialize CAL \n");

        // Get device count and initialize them
        calDeviceGetCount(&_numDevices);
        CHECK_CONDITION(_numDevices > 0, "No CAL devices available \n");

        // In this release we are not going to support multi-GPU
        // We need not to initialize all the devices available 
        _numDevices = 1;

        char *adapterEnv;
        int which_device = 0;
        if ((adapterEnv = getenv("AMDPL_ADAPTER")))
            which_device = atoi(adapterEnv);

        CalDevice* device = new CalDevice(which_device);
        if(!device->initialize())
        {
            delete device;
            return false;
        }

        _devices = device;
        _bufferMgr = new CalBufferMgr(device);

        return true;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Default handler that is used in case user has not provided any hadler
    //! Gives a warning and throws bad_alloc exception. So the user gets opportunity 
    //! to handle this exception in case he has not provided a callback.
    //!
    ////////////////////////////////////////////////////////////////////////////////

    void defaultHandler()
    {
        std::cout << "Failed to allocate memory.\n";
        throw std::bad_alloc();
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Function to set memory handle
    //!
    ////////////////////////////////////////////////////////////////////////////////

    void setMemoryHandle(MemoryHandler handler)
    {
        std::set_new_handler(handler);
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Function regestered in atexit call
    //!
    //! A friend function that calls runtime destructor.
    //! This function is called as soon as application exits.
    //!
    ////////////////////////////////////////////////////////////////////////////////

    void cleanup()
    {
        CalRuntime*& runtime = CalRuntime::_runtime;
        if (runtime != NULL)
        {
            delete runtime;
            runtime = NULL;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Static instance of singleton class
    //!
    ////////////////////////////////////////////////////////////////////////////////

    CalRuntime* CalRuntime::_runtime = NULL;

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Static method to get Runtime Instance.
    //!
    //! Calls Create method on backend runtime if instance is NULL.
    //!
    ////////////////////////////////////////////////////////////////////////////////

    CalRuntime* CalRuntime::getInstance()
    {
        if (_runtime == NULL)
        {
            MemoryHandler oldHandle = std::set_new_handler(defaultHandler);
            if(oldHandle)
            {
                std::set_new_handler(oldHandle);
            }

            _runtime = CalRuntime::create();

            if(_runtime == NULL)
            {
                if(_runtime == NULL)
                {
                    std::cout << "Failed to initialize the runtime. Application exiting\n";
                    exit(1);
                }
            }

            // Register the callback for application exit
            // to make sure we cleanup everything
            atexit(cleanup);
        }
        return _runtime;
    }
}