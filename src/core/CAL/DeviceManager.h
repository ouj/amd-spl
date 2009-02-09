//
//
//
//  @ Project : AMD-SPL
//  @ File Name : DeviceManager.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_DEVICEMANAGER_H)
#define _DEVICEMANAGER_H
#include "cal.h"
#include <vector>

// DeviceManager class is the manages all the devices.
namespace amdspl
{
    namespace core
    {
        namespace cal
        {
			class Device;
            class DeviceManager
            {
                friend class Runtime;
            public:
                bool addDevice(unsigned short id = 0, CALdevice device = NULL);
                unsigned short getDeviceNum();
                unsigned short getSysDeviceNum();
                // Get the device by id. return NULL if the specific device is not assigned to SPL
                Device* getDeviceByID(unsigned short id = 0);
                // Get the default device.
                Device* getDefaultDevice();
                // Set the default device ID, return true if sucess, false if the device with the specific ID is not assigned to SPL.
                bool setDefaultDevice(unsigned short id);
                CALdevice* getDeviceHandles();
            protected:
                DeviceManager();
                ~DeviceManager();
                bool initialize();

                // the list of pointers to all the devices, order by device Id. If the device is not initialized, the pointer is set to NULL.
                std::vector<Device*> _devices;
                // The number of devices assigned to the SPL.
                unsigned short _devicesNum;
                // The number of devices in the system, which is larger or equal to the devices in the device list.
                unsigned short _sysDevicesNum;
                // The id of default device
                unsigned short _defaultDeviceId;
            };
        }
    }
}

#endif  //_DEVICEMANAGER_H
