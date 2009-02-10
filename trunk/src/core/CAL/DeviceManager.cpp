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
#include "CommonDefs.h"
#include "Device.h"
#include <cassert>

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
                // Get device count and initialize them
                calDeviceGetCount(&_sysDevicesNum);
                CHECK_CONDITION(_sysDevicesNum > 0, "No CAL devices available \n");

                _devices.resize(_sysDevicesNum, NULL); //initialize the list.

				return true;
			}

            bool DeviceManager::addDevice(unsigned short id, CALdevice deviceHandle)
            {
                Device* pDevice = new Device(id, deviceHandle);
                assert(pDevice);
                CHECK_CONDITION(pDevice, "Failed to create the device object\n");

                if (!pDevice->initialize())
                {
                    fprintf(stderr, "Failed to initialize the device, Device Id %d", id);
                    SAFE_DELETE(pDevice);
                }

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
