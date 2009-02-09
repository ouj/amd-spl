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
    bool AmdSpl::InitializeSPL(DEVICE_LIST_ITEM *devices, unsigned short numDevices, int defaultDeviceIdx)
    {
		return true;
    }
    
	//////////////////////////////////////////////////////////////////////////
	//! \brief This the initialization function of the amd-spl library.
	//!
	//! This function should be the first function call of the amd-spl
	//! library. (Note: currently this function does nothing)
	//////////////////////////////////////////////////////////////////////////
    bool AmdSpl::CleanupSPL()
    {
		return true;
    }
    
}
