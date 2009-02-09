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

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
			Device::Device(unsigned short) : _shutDownOnDestroy(true)
            {
            
            }
            
			Device::Device(unsigned short id, CALdevice device) : _shutDownOnDestroy(false)
            {
            
            }
            
            Device::~Device()
            {
            
            }
            
            bool Device::initialize()
            {
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
