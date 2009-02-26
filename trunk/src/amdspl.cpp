//
//
//
//  @ Project : AMD-SPL
//  @ File Name : AmdSpl.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#include "AmdSpl.h"
#include "CommonDefs.h"
#include "Runtime.h"
#include "DeviceManager.h"
#include <cassert>

using namespace amdspl::core::cal;

namespace amdspl
{

    DEVICE_LIST_ITEM::DEVICE_LIST_ITEM(unsigned short deviceId, CALdevice deviceHandle)
    {
        this->deviceId = deviceId;
        this->deviceHandle = deviceHandle;
    }

    //////////////////////////////////////////////////////////////////////////
    //! \brief This the initialization function of the amd-spl library.
    //!
    //! This function should be the first function call of the amd-spl
    //! library. (Note: currently this function does nothing)
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
    //! \brief This the initialization function of the amd-spl library.
    //!
    //! This function should be the first function call of the amd-spl
    //! library. (Note: currently this function does nothing)
    //////////////////////////////////////////////////////////////////////////
    SPL_RESULT AmdSpl::CleanupSPL()
    {
        Runtime::destroy();
        return SPL_RESULT_OK;
    }
    
}
