#if !defined(_DEVICEMANAGER_H)
#define _DEVICEMANAGER_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		DeviceManager.h
//!	\date 		27:2:2009   22:18
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of DeviceManager class.
//!
//////////////////////////////////////////////////////////////////////////
#include "cal.h"
#include <vector>

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
			class Device;
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	 This class provide interface for device management. It 
            //!          contains factory method for Device. The object is created 
            //!          when runtime is initialized and deleted when the runtime is 
            //!          destroyed.
            //!
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
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
                CALint          _devicesNum;
                // The number of devices in the system, which is larger or equal to the devices in the device list.
                CALuint         _sysDevicesNum;
                // The id of default device
                CALint          _defaultDeviceId;
            private:
                // The list of device handle, used by BufferManager to Create remote buffer.
                std::vector<CALdevice> _deviceHandles;
            };
        }
    }
}

#endif  //_DEVICEMANAGER_H
