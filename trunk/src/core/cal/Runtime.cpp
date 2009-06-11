#include <cassert>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		Runtime.cpp
//!	\date 		27:2:2009   15:51
//!	\author		Jiawe Ou
//!	
//!	\brief		Contains definition of Runtime class
//!
//////////////////////////////////////////////////////////////////////////
#include "RuntimeDefs.h"
#include "CommonDefs.h"

namespace amdspl
{
    //////////////////////////////////////////////////////////////////////////
    //! \brief namespace for AMD-SPL runtime classes
    //////////////////////////////////////////////////////////////////////////
    namespace core
    {
        //////////////////////////////////////////////////////////////////////////
        //! \brief namespace for CAL implementation of AMD-SPL runtime
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief      The memory handler function type.
            //!
            //////////////////////////////////////////////////////////////////////////
            typedef void(*MemoryHandler)();

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return void
            //!
            //! \brief  This is the default handler for memory allocation error.
            //!
            //////////////////////////////////////////////////////////////////////////
            void defaultHandler()
            {
                fprintf(stderr, "Failed to allocate memory.\n");
                throw std::bad_alloc();
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	handler The memory handler function pointer
            //! \return	void
            //!
            //! \brief	Function to set memory handle.
            //!
            //////////////////////////////////////////////////////////////////////////void
            void setMemoryHandle(MemoryHandler handler)
            {
                std::set_new_handler(handler);
            }


			Runtime* Runtime::_runtime = 0;


            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Runtime*
            //!
            //! \brief	The method to get the singleton instance pointer. When first 
            //!         time this method is called, a new runtime instance is 
            //!         allocated and initialized.
            //!
            //////////////////////////////////////////////////////////////////////////
            Runtime* Runtime::getInstance()
            {
				if (!_runtime)
				{
                    MemoryHandler oldHandle = std::set_new_handler(defaultHandler);
                    if(oldHandle)
                    {
                        std::set_new_handler(oldHandle);
                    }

					_runtime = new Runtime();
                    assert(_runtime);
                    if (_runtime)
                    {
                        if(!_runtime->create())
                        {
                            SAFE_DELETE(_runtime);
                            return NULL;
                        }
                        atexit(destroy); //Function registered in atexit call
                    } 
				}
				return _runtime;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool
            //!
            //! \brief	Runtime initialization method. It initialize CAL and create
            //!         all the manager classes.When initializing CAL, Runtime will 
            //!         check the return value of calInit(). If it returns 
            //!         CAL_RESULT_OK, it means that CAL initialized successfully. If 
            //!         it returns CAL_RESULT_ALREADY, it means that CAL is already 
            //!         initialized somewhere else. In that case, _shutdownOnDestroy 
            //!         is set to false, and the CAL will not be shutdown when the
            //!         Runtime is destoyed.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Runtime::create()
            {
				assert(_runtime);
				if (!_runtime)
				{
					return false;
				}

                CALresult result;

                // Initialize CAL
                result = calInit();
                if (result == CAL_RESULT_ALREADY)
                {
                    _shutdownOnDestroy = false;
                }
                else if (result != CAL_RESULT_OK)
                {
                    LOG_ERROR("Failed to initialize CAL\n");
                    return false;
                }

				//initialize device manager
				_deviceMgr = new DeviceManager();
                if (!_deviceMgr->initialize())
                {
                    LOG_ERROR("Failed to initialize device manager\n");
                    goto SAFE_DELETE_ALL_ON_ERROR;
                }

                _bufferMgr = new BufferManager();
                if (!_bufferMgr->initialize())
                {
                    LOG_ERROR("Failed to initialize buffer manager\n");
                    goto SAFE_DELETE_ALL_ON_ERROR;
                }

                _programMgr = new ProgramManager();
                if (!_programMgr->initialize())
                {
                    LOG_ERROR("Failed to initialize program manager\n");
                    goto SAFE_DELETE_ALL_ON_ERROR;
                }

                _counterMgr = new CounterManager();
                if (!_counterMgr->initialize())
                {
                    LOG_ERROR("Failed to initialize counter manager\n");
                    goto SAFE_DELETE_ALL_ON_ERROR;
                }

				return true;

SAFE_DELETE_ALL_ON_ERROR:
                SAFE_DELETE(_bufferMgr);
                SAFE_DELETE(_programMgr);
                SAFE_DELETE(_deviceMgr);
                SAFE_DELETE(_counterMgr);
                return false;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	void
            //!
            //! \brief	Runtime destruction method. It destroy and delete the singleton
            //!         instance of Runtime class. 
            //!
            //////////////////////////////////////////////////////////////////////////
            void Runtime::destroy()
            {
                Runtime*& runtime = Runtime::_runtime;
                if (runtime != NULL)
                {
                    delete runtime;
                    runtime = NULL;
                }
            }

            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	DeviceManager*
            //!
            //! \brief	Method to get the DeviceManager instance pointer.
            //!
            //////////////////////////////////////////////////////////////////////////
            DeviceManager* Runtime::getDeviceManager()
            {
				assert(_deviceMgr);
				return _deviceMgr;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	BufferManager*
            //!
            //! \brief	Method to get the BufferManager instance pointer
            //!
            //////////////////////////////////////////////////////////////////////////
            BufferManager* Runtime::getBufferManager()
            {
				assert(_bufferMgr);
				return _bufferMgr;	
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	ProgramManager*
            //!
            //! \brief	Method to get the ProgramManager instance pointer
            //!
            //////////////////////////////////////////////////////////////////////////
            ProgramManager* Runtime::getProgramManager()
            {
				assert(_programMgr);
				return _programMgr;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CounterManager*
            //!
            //! \brief	Method to get the CounterManager instance pointer
            //!
            //////////////////////////////////////////////////////////////////////////
            CounterManager* Runtime::getCounterManager()
            {
				assert(_counterMgr);
				return _counterMgr;
            }

			//////////////////////////////////////////////////////////////////////////
			//!
			//! \return	Constructor
			//!
			//! \brief	Construct the Runtime instance, it is a protected member, can 
            //!         only be called by Runtime::getInstance(); The runtime will not  
            //!         be available until Runtime::create() is called.
			//!
			//////////////////////////////////////////////////////////////////////////
			Runtime::Runtime() : _programMgr(0), _bufferMgr(0), 
				_deviceMgr(0)
            {
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy the Runtime object. Safely delete all the managers 
            //!         and call calShutdown() if _shutdownOnDestroy is true.
            //!
            //////////////////////////////////////////////////////////////////////////
            Runtime::~Runtime()
            {
                SAFE_DELETE(_deviceMgr);
                SAFE_DELETE(_bufferMgr);
                SAFE_DELETE(_programMgr);
                SAFE_DELETE(_counterMgr);
                
                // Finally, shutdown the CAL
                if (_shutdownOnDestroy)
                {
                    calShutdown();
                }
            }
            
        }
    }
}
