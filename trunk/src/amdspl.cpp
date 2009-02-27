//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		amdspl.cpp
//!	\date 		27:2:2009   16:43
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of AmdSpl.
//!
//////////////////////////////////////////////////////////////////////////
#include "AmdSpl.h"
#include "CommonDefs.h"
#include "Runtime.h"
#include "DeviceManager.h"
#include <cassert>

using namespace amdspl::core::cal;

//////////////////////////////////////////////////////////////////////////
//!
//! \brief The namespace of AMD-SPL
//!
///////////////////////////////////////////////////
namespace amdspl
{

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \return Constructor
    //!
    //! \brief  Initialize the DEVICE_LIST_ITEM with the device Id and Device
    //!         handle.
    //!
    //////////////////////////////////////////////////////////////////////////
    DEVICE_LIST_ITEM::DEVICE_LIST_ITEM(unsigned short deviceId, CALdevice deviceHandle)
    {
        this->deviceId = deviceId;
        this->deviceHandle = deviceHandle;
    }

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief  This the initialization function of the amd-spl library.
    //!         This function should be the first function call of the amd-spl
    //!         library. 
    //!
    //////////////////////////////////////////////////////////////////////////
    SPL_RESULT AmdSpl::InitializeSPL(DEVICE_LIST_ITEM *devices, unsigned short numDevices, int defaultDeviceIdx)
    {
        if (!devices)
        {
            return SPL_RESULT_INVALID_ARGUMENT;
        }

        if (numDevices <= 0)
        {
            return SPL_RESULT_INVALID_ARGUMENT;
        }

        Runtime* runtime = Runtime::getInstance();
        if (runtime == NULL)
            return SPL_RESULT_ERROR;
        else
        {
            DeviceManager* pDeviceMgr = runtime->getDeviceManager();
            for (unsigned short i = 0; i < numDevices; i++)
            {
                if(!pDeviceMgr->addDevice(devices[i].deviceId, devices[i].deviceHandle))
                {
                    CleanupSPL();
                    return SPL_RESULT_ERROR;
                }
            }
            return SPL_RESULT_OK;
        }
    }
    
    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief  This the initialization function of the AMD-SPL library.
    //!         This function should be the last function call of the amd-spl
    //!         library. 
    //!
    //////////////////////////////////////////////////////////////////////////
    SPL_RESULT AmdSpl::CleanupSPL()
    {
        Runtime::destroy();
        return SPL_RESULT_OK;
    }
    
}
