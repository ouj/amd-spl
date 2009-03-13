#ifndef AMDSPL_DEVICEMANAGER_H
#define AMDSPL_DEVICEMANAGER_H
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
#include "SplDefs.h"
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
            //! \brief	 DeviceManager class provide interface for device management. 
            //!          It contains factory method for Device. The object is created 
            //!          when runtime is initialized and deleted when the runtime is 
            //!          destroyed.
            //!
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class SPL_EXPORT DeviceManager
            {
                friend class Runtime;
            public:
                bool assignDevice(unsigned short id = 0, CALdevice device = NULL);
                unsigned short getDeviceNum();
                unsigned short getSysDeviceNum();
                Device* getDeviceByID(unsigned short id = 0);
                Device* getDefaultDevice();
                bool setDefaultDevice(unsigned short id);
                CALdevice* getDeviceHandles();
            protected:
                DeviceManager();
                ~DeviceManager();
                bool initialize();

                //! \brief	the list of pointers to all the devices, order 
                //!         by device Id. If the device is not initialized, 
                //!         the pointer is set to NULL.
                std::vector<Device*> _devices;
                //! \brief  The number of devices assigned to the SPL.
                CALint          _devicesNum;
                //! \brief  The number of devices in the system, which is 
                //!         larger or equal to the devices in the device list.
                CALuint         _sysDevicesNum;
                //! \brief  The id of default device
                CALint          _defaultDeviceId;
            private:
                //! \brief  The list of device handle, used by BufferManager
                //!         to Create remote buffer.
                std::vector<CALdevice> _deviceHandles;
            };
        }
    }
}

#endif  //AMDSPL_DEVICEMANAGER_H
