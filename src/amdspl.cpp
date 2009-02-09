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
    SPL_ERROR AmdSpl::InitializeSPL(DEVICE_LIST_ITEM *devices, unsigned short numDevices, int defaultDeviceIdx)
    {
        core::cal::Runtime* runtime = core::cal::Runtime::getInstance();
        if (runtime == NULL)
            return SPL_RESULT_ERROR;

        if (runtime->create(devices, numDevices))
        {
            return SPL_RESULT_OK;
        }
        else
        {
            return SPL_RESULT_NOT_INITIALIZED;
        }
    }
    
    //////////////////////////////////////////////////////////////////////////
    //! \brief This the initialization function of the amd-spl library.
    //!
    //! This function should be the first function call of the amd-spl
    //! library. (Note: currently this function does nothing)
    //////////////////////////////////////////////////////////////////////////
    SPL_ERROR AmdSpl::CleanupSPL()
    {
        return SPL_RESULT_OK;
    }
    
}
