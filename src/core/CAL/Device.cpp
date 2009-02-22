//
//
//
//  @ Project : AMD-SPL
//  @ File Name : Device.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#include "Device.h"
#include "RuntimeDefs.h"
#include <cassert>
#include <stdio.h>

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            Device::Device(unsigned short id, CALdevice device) : 
                _Id(id), _deviceHandle(device), _context(0), _shutDownOnDestroy(false)
            {

            }
            
            Device::~Device()
            {
                CALresult result;
                // Cleanup of context and Device handle
                if(_context)
                {
                    result = calCtxDestroy(_context);
                    if (result != CAL_RESULT_OK)
                    {
                        LOG_ERROR("Failed to destroy context!\n");
                    }
                }

                // if device handle is initialize somewhere else,
                // we will set the shutdown on destroy flag to false
                // we will not destroy the device handle when exit.
                if(_deviceHandle && _shutDownOnDestroy)
                {
                    result = calDeviceClose(_deviceHandle);
                    if (result != CAL_RESULT_OK)
                    {
                        LOG_ERROR("Failed to close device!\n");
                    }
                }
            }
            
            bool Device::initialize()
            {
                CALresult result;
                if (_deviceHandle == NULL)
                {
                    _shutDownOnDestroy = true;
                    result = calDeviceOpen(&_deviceHandle, _Id);
                    CHECK_CAL_RESULT(result, "Failed to open CAL device \n");
                }

                result = calDeviceGetInfo(&_deviceInfo, _Id);
                CHECK_CAL_RESULT(result, "Failed to get info on CAL device \n");

                _deviceAttribs.struct_size = sizeof(CALdeviceattribs);
                result = calDeviceGetAttribs(&_deviceAttribs, _Id);
                CHECK_CAL_RESULT(result, "Failed to get CAL device attributes\n");

                // Create the device context
                result = calCtxCreate(&_context, _deviceHandle);
                CHECK_CAL_RESULT(result, "Failed to create context on CAL device \n");

                return true;
            }
            
            CALdevice Device::getHandle()
            {
                assert(_deviceHandle);
                return _deviceHandle;
            }
            
            const CALdeviceinfo& Device::getInfo()
            {
                return _deviceInfo;
            }

            const CALdevicestatus& Device::getStatus()
            {
                memset(&_deviceStatus, 0, sizeof(CALdevicestatus));
                _deviceStatus.struct_size = sizeof(CALdevicestatus);
                CALresult result = calDeviceGetStatus(&_deviceStatus, _deviceHandle);
                LOG_CAL_RESULT_ERROR(result, "Failed to get device status\n");
                return _deviceStatus;
            }
            
            const CALdeviceattribs& Device::getAttribs()
            {
                return _deviceAttribs;
            }
            
            CALcontext Device::getContext()
            {
                assert(_context);
                return _context;
            }
            
            unsigned short Device::getId()
            {
                return _Id;
            }
            
        }
    }
}
