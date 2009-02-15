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

using namespace std;

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
                vector<Device*>::iterator it = _devices.begin();
                while (it != _devices.end())
                {
                    SAFE_DELETE(*it);
                    it++;
                }
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
                    fprintf(stderr, "Failed to initialize the device, Device Id: %d, Handle: 0x%X\n", id, deviceHandle);
                    SAFE_DELETE(pDevice);
                    return false;
                }

                _devices[pDevice->getId()] = pDevice;
                _devicesNum++;

                _deviceHandles.push_back(pDevice->getHandle());

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
                if (id >= _devices.size())
                {
                    return NULL;
                }

                return _devices[id];
            }
            
            Device* DeviceManager::getDefaultDevice()
            {
                return _devices[_defaultDeviceId];
            }
            
            bool DeviceManager::setDefaultDevice(unsigned short id)
            {
                if (id >= _devices.size())
                {
                    return false;
                }
                else if (_devices[id] != NULL)
                {
                    _defaultDeviceId = id;
                    return true;
                }
                else
                    return false;
            }
            
            CALdevice* DeviceManager::getDeviceHandles()
            {
                return &_deviceHandles[0];
            }         
        }
    }
}
