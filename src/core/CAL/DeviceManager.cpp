//
//
//
//  @ Project : AMD-SPL
//  @ File Name : DeviceManager.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//

#include "DeviceManager.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
			DeviceManager::DeviceManager() : _devicesNum(0), _sysDevicesNum(0), _defaultDeviceId(0)
			{

			}

			DeviceManager::~DeviceManager()
			{

			}

			bool DeviceManager::initialize()
			{

				return true;
			}

            bool DeviceManager::addDevice(unsigned short id, CALdevice device)
            {
				return true;
            }
            
            unsigned short DeviceManager::getDeviceNum()
            {
                return _devicesNum;
            }
            
            unsigned short DeviceManager::getSysDeviceNum()
            {
                return _sysDevicesNum;
            }
            
            Device* DeviceManager::getDeviceByID(unsigned short id)
            {
                return NULL;
            }
            
            Device* DeviceManager::getDefaultDevice()
            {
                return NULL;
            }
            
            bool DeviceManager::setDefaultDevice(unsigned short id)
            {
                return true;
            }
            
            CALdevice* DeviceManager::getDeviceHandles()
            {
                return NULL;
            }         
        }
    }
}
