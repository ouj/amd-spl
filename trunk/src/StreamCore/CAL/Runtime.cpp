//
//
//
//  @ Project : AMD-SPL
//  @ File Name : Runtime.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//

#include "Runtime.h"
#include <cassert>
#include "DeviceManager.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
			Runtime* Runtime::_runtime = 0;

            Runtime* Runtime::getInstance()
            {
				if (!_runtime)
				{

					_runtime = new Runtime();
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

				//initialize device manager
				_deviceMgr = new DeviceManager();
				for (unsigned short i = 0; i < numDevices; i++)
				{
					_deviceMgr->addDevice();
				}
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
            
            }
            
        }
    }
}
