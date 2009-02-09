//
//
//
//  @ Project : AMD-SPL
//  @ File Name : Runtime.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//
#include <cassert>
#include <stdio.h>

#include "Runtime.h"
#include "CommonDefs.h"
#include "DeviceManager.h"
#include "amdspl.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {

            ////////////////////////////////////////////////////////////////////////////////
            //!
            //! \brief Default handler that is used in case user has not provided any hadler
            //! Gives a warning and throws bad_alloc exception. So the user gets opportunity 
            //! to handle this exception in case he has not provided a callback.
            //!
            ////////////////////////////////////////////////////////////////////////////////
            void defaultHandler()
            {
                fprintf(stderr, "Failed to allocate memory.\n");
                throw std::bad_alloc();
            }

            ////////////////////////////////////////////////////////////////////////////////
            //!
            //! \brief Function to set memory handle
            //!
            ////////////////////////////////////////////////////////////////////////////////
            void
                setMemoryHandle(MemoryHandler handler)
            {
                std::set_new_handler(handler);
            }

            ////////////////////////////////////////////////////////////////////////////////
            //!
            //! \brief Function regstered in atexit call
            //!
            //! A friend function that calls runtime destructor.
            //! This function is called as soon as application exits.
            //!
            ////////////////////////////////////////////////////////////////////////////////

            void
                atExitCleanUp()
            {
                Runtime*& runtime = Runtime::_runtime;
                if (runtime != NULL)
                {
                    delete runtime;
                    runtime = NULL;
                }
            }


			Runtime* Runtime::_runtime = 0;
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
                    atexit(atExitCleanUp);
				}
				return _runtime;
            }
            
            bool Runtime::create(DEVICE_LIST_ITEM *devices, unsigned short numDevices)
            {
				assert(!_runtime);
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
                    fprintf(stderr, "Failed to initialize CAL\n");
                    return false;
                }

				//initialize device manager
				_deviceMgr = new DeviceManager();
				for (unsigned short i = 0; i < numDevices; i++)
				{
					_deviceMgr->addDevice(devices[i].deviceId, devices[i].deviceHandle);
				}
				return true;
            }
            
            bool Runtime::destroy()
            {
                if (_shutdownOnDestroy)
                {
                    calShutdown();
                }

                SAFE_DELETE(_deviceMgr);
                //SAFE_DELETE(_programMgr);
                //SAFE_DELETE(_bufferMgr);
                //SAFE_DELETE(_constBufferPool);

                return true;
            }

            DeviceManager* Runtime::getDeviceManager()
            {
				assert(_deviceMgr);
				return _deviceMgr;
            }
            
            ConstBufferPool* Runtime::getConstBufferPool()
            {
				assert(_constBufferPool);
				return _constBufferPool;
            }
            
            BufferManager* Runtime::getBufferManager()
            {
				assert(_bufferMgr);
				return _bufferMgr;	
            }
            
            ProgramManager* Runtime::getProgramManager()
            {
				assert(_programMgr);
				return _programMgr;
            }
            
			Runtime::Runtime() : _programMgr(0), _bufferMgr(0), 
				_deviceMgr(0), _constBufferPool(0)
            {
            
            }
            
            Runtime::~Runtime()
            {
                destroy();
            }
            
        }
    }
}
