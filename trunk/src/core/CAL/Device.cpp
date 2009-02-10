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

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
			Device::Device(unsigned short id) : 
                _Id(id), _device(NULL), _shutDownOnDestroy(false)
            {
                
            }
            
			Device::Device(unsigned short id, CALdevice device) : 
                _Id(id), _device(device), _shutDownOnDestroy(false)
            {

            }
            
            Device::~Device()
            {
                // Cleanup of context and Device handle
                if(_context)
                {
                    calCtxDestroy(_context);
                }

                // if device handle is initialize somewhere else,
                // we will set the shutdown on destroy flag to false
                // we will not destroy the device handle when exit.
                if(_device && _shutDownOnDestroy)
                {
                    calDeviceClose(_device);
                }
            }
            
            bool Device::initialize()
            {
                CALresult result;
                if (_device == NULL)
                {
                    _shutDownOnDestroy = true;
                    result = calDeviceOpen(&_device, _Id);
                    CHECK_CAL_RESULT(result, "Failed to open CAL device \n");
                }

                result = calDeviceGetInfo(&_deviceInfo, _Id);
                CHECK_CAL_RESULT(result, "Failed to get info on CAL device \n");

                _deviceAttribs.struct_size = sizeof(CALdeviceattribs);
                result = calDeviceGetAttribs(&_deviceAttribs, _Id);
                CHECK_CAL_RESULT(result, "Failed to get CAL device attributes\n");

                // Create the device context
                result = calCtxCreate(&_context, _device);
                CHECK_CAL_RESULT(result, "Failed to create context on CAL device \n");

                return true;
            }
            
            CALdevice Device::getHandle()
            {
                return _device;
            }
            
            CALdeviceinfo Device::getInfo()
            {
                return _deviceInfo;
            }
            
            CALdeviceattribs Device::getAttribs()
            {
                return _deviceAttribs;
            }
            
            CALcontext Device::getContext()
            {
                return _context;
            }
            
            unsigned short Device::getId()
            {
                return _Id;
            }
            
        }
    }
}
