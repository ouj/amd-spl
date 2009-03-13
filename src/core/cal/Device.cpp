//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		Device.cpp
//!	\date 		28:2:2009   22:17
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of Device class.
//!
//////////////////////////////////////////////////////////////////////////
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
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	id      The device ID
            //! \param	device  he device handle if the device is initialized
            //!                 somewhere else. NULL if the device is not 
            //!                 initialized elsewhere.
            //! \return	Constructor
            //!
            //! \brief	Construct the Device object. It will not be available until
            //!         Device::initialize() is called. if device handle is initialize 
            //!         somewhere else, the shutdown on destroy flag will be set to 
            //!         false.
            //!
            //////////////////////////////////////////////////////////////////////////
            Device::Device(unsigned short id, CALdevice device) : 
                _Id(id), _deviceHandle(device), _context(0), _shutDownOnDestroy(false)
            {

            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy the Device object. The context associated to the 
            //!         device will be flushed and destroyed. If the shutdown on 
            //!         destroy flag is set to false, the CAL device handle will 
            //!         not be destroyed at exit.
            //!
            //////////////////////////////////////////////////////////////////////////
            Device::~Device()
            {
                flush();
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
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool True if the device is successfully initialized.
            //!              False if there is an error during the initialization.
            //!
            //! \brief	Initialize the Device object. In this method, the CAL device
            //!         will be open if it is needed. The device information and 
            //!         attributes will be retrieved. The context of the device will
            //!         be created.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Device::initialize()
            {
                CALresult result;
                if (_deviceHandle == 0)
                {
                    _shutDownOnDestroy = true;
                    result = calDeviceOpen(&_deviceHandle, _Id);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to open CAL device \n");
                }

                result = calDeviceGetInfo(&_deviceInfo, _Id);
                CHECK_CAL_RESULT_ERROR(result, "Failed to get info on CAL device \n");

                _deviceAttribs.struct_size = sizeof(CALdeviceattribs);
                result = calDeviceGetAttribs(&_deviceAttribs, _Id);
                CHECK_CAL_RESULT_ERROR(result, "Failed to get CAL device attributes\n");

                // Create the device context
                result = calCtxCreate(&_context, _deviceHandle);
                CHECK_CAL_RESULT_ERROR(result, "Failed to create context on CAL device \n");

                return true;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CALdevice The CAL handle of the device
            //!
            //! \brief	Get the device handle.
            //!
            //////////////////////////////////////////////////////////////////////////
            CALdevice Device::getHandle()
            {
                assert(_deviceHandle);
                return _deviceHandle;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	const CALdeviceinfo& Device information.
            //!
            //! \brief	Get the device information
            //!
            //////////////////////////////////////////////////////////////////////////
            const CALdeviceinfo& Device::getInfo()
            {
                return _deviceInfo;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	const CALdevicestatus& Device status, including memory usage
            //!               information.
            //!
            //! \brief	Get the device status.
            //!
            //////////////////////////////////////////////////////////////////////////
            const CALdevicestatus& Device::getStatus()
            {
                memset(&_deviceStatus, 0, sizeof(CALdevicestatus));
                _deviceStatus.struct_size = sizeof(CALdevicestatus);
                CALresult result = calDeviceGetStatus(&_deviceStatus, _deviceHandle);
                LOG_CAL_RESULT_ERROR(result, "Failed to get device status\n");
                return _deviceStatus;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	const CALdeviceattribs& Device attributes.
            //!
            //! \brief	Get the device attributes.
            //!
            //////////////////////////////////////////////////////////////////////////
            const CALdeviceattribs& Device::getAttribs()
            {
                return _deviceAttribs;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CALcontext The CAL context associated to the device
            //!
            //! \brief	Get the CAL context associated to the device.
            //!
            //////////////////////////////////////////////////////////////////////////
            CALcontext Device::getContext()
            {
                return _context;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	unsigned short The device ID.
            //!
            //! \brief	Get the device ID
            //!
            //////////////////////////////////////////////////////////////////////////
            unsigned short Device::getId()
            {
                return _Id;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool True if all the commands a successfully flushed. 
            //!              False if an error happens.
            //!
            //! \brief	Flush all the commands to the device.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Device::flush()
            {
                CALresult result = calCtxFlush(_context);
                CHECK_CAL_RESULT_ERROR(result, "Unable to flush the context\n");
                return true;
            }
        }
    }
}
