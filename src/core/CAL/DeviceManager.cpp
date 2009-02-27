//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		DeviceManager.cpp
//!	\date 		27:2:2009   22:18
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of DeviceManager class.
//!
//////////////////////////////////////////////////////////////////////////
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
			//////////////////////////////////////////////////////////////////////////
			//!
			//! \return	Constructor
			//!
			//! \brief	Construct DeviceManager and initialize all the members to its 
            //!         default value. But it will not be initialized until 
            //!         DeviceManager::initialize() is called.
			//!
			//////////////////////////////////////////////////////////////////////////
			DeviceManager::DeviceManager() : _devicesNum(0), _sysDevicesNum(0), _defaultDeviceId(-1)
			{

			}

			//////////////////////////////////////////////////////////////////////////
			//!
			//! \return	Destructor
			//!
			//! \brief	Destroy the DeviceManager. It also destroys all the devices 
            //!         associated to it.
			//!
			//////////////////////////////////////////////////////////////////////////
			DeviceManager::~DeviceManager()
			{
                vector<Device*>::iterator it = _devices.begin();
                while (it != _devices.end())
                {
                    SAFE_DELETE(*it);
                    it++;
                }
			}

			//////////////////////////////////////////////////////////////////////////
			//!
			//! \return	bool    True if DeviceManager is initialized successfully.
            //!                 False if there is an error during initialization.
			//!
			//! \brief	Initialize the DeviceManager. It query the device number of 
            //!         the system and allocate space for all device pointers.
			//!
			//////////////////////////////////////////////////////////////////////////
			bool DeviceManager::initialize()
			{
                // Get device count and initialize them
                calDeviceGetCount(&_sysDevicesNum);
                CHECK_CONDITION(_sysDevicesNum > 0, "No CAL devices available \n");

                _devices.resize(_sysDevicesNum, NULL); //initialize the list.

				return true;
			}

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	id              The device ID
            //! \param	deviceHandle    The device handle if the device is initialized
            //!                         somewhere else. NULL if the device is not 
            //!                         initialized elsewhere.
            //! \return	bool            True if a device is successfully added. False
            //!                         if failed to add a device.
            //!
            //! \brief	                Add a device to the device manager. If the 
            //!                         device with specific ID is initialized 
            //!                         somewhere else the device handle of that device 
            //!                         should be provided.
            //!
            //////////////////////////////////////////////////////////////////////////
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

                if(_defaultDeviceId == -1)
                {
                    _defaultDeviceId = pDevice->getId();
                }

                _devices[pDevice->getId()] = pDevice;
                _devicesNum++;

                _deviceHandles.push_back(pDevice->getHandle());

				return true;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	unsigned short The number of devices associated to the 
            //!         DeviceManager.
            //!
            //! \brief	Get the number of devices associated to the DeviceManager.
            //!
            //////////////////////////////////////////////////////////////////////////
            unsigned short DeviceManager::getDeviceNum()
            {
                return _devicesNum;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	unsigned short The number of devices in the system.
            //!
            //! \brief	Get the number of devices in the system.
            //!
            //////////////////////////////////////////////////////////////////////////
            unsigned short DeviceManager::getSysDeviceNum()
            {
                return _sysDevicesNum;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	id      The ID of the device.
            //! \return	Device* The pointer to the device with specific ID if the Device
            //!                 is associated to the DeviceManager. NULL if the device 
            //!                 with specific ID is not associated to the DeviceManager.
            //!
            //! \brief	Get the Device with the specific ID.
            //!
            //////////////////////////////////////////////////////////////////////////
            Device* DeviceManager::getDeviceByID(unsigned short id)
            {
                if (id >= _devices.size())
                {
                    return NULL;
                }

                return _devices[id];
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Device* The default device pointer
            //!
            //! \brief	Get the default device. NULL if there is no devices associated
            //!         to the DeviceManager.
            //!
            //////////////////////////////////////////////////////////////////////////
            Device* DeviceManager::getDefaultDevice()
            {
                if (_defaultDeviceId == -1 || _defaultDeviceId > (int)_devices.size())
                {
                    return NULL;
                }
                return _devices[_defaultDeviceId];
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	id      The ID of the device.
            //! \return	bool    True if the default device is set successfully. False 
            //!                 if the device with the specific ID is not associated
            //!                 to the DeviceManager.
            //!
            //! \brief	Set the default device.
            //!
            //////////////////////////////////////////////////////////////////////////
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
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CALdevice* Device hanlde list.
            //!
            //! \brief	Get the device handle list. This method is mainly used to 
            //!         create the RemoteBuffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            CALdevice* DeviceManager::getDeviceHandles()
            {
                return &_deviceHandles[0];
            }         
        }
    }
}
