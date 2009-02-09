#if !defined(_AMDSPL_H)
#define _AMDSPL_H
//
//  @ Project : AMD-SPL
//  @ File Name : AmdSpl.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//
////////////////////////////////////////////////////////////////////////////////
//!
//! \file amdspl.h
//!
//! \brief Contains declaration of the initialization function and cleanup 
//!        function. it also include headers that are necessary to run the SPL 
//!
////////////////////////////////////////////////////////////////////////////////


#include "cal.h"

#ifdef AMD_SPL_EXPORT
#define SPL_EXPORT __declspec(dllexport)
#else
#define SPL_EXPORT
#endif

//////////////////////////////////////////////////////////////////////////
//!
//! \brief The namespace of AMD-SPL
//!
///////////////////////////////////////////////////
namespace amdspl
{
	struct SPL_EXPORT DEVICE_LIST_ITEM
	{
	public:
		DEVICE_LIST_ITEM(unsigned short deviceId = 0, CALdevice deviceHandle = 0);
		unsigned short deviceId;
		CALdevice deviceHandle;
	};

    class SPL_EXPORT AmdSpl
    {
    public:
        static bool InitializeSPL(DEVICE_LIST_ITEM *devices = 0, unsigned short numDevices = 0, int defaultDeviceIdx = 0);
        static bool CleanupSPL();
    };
}

#endif  //_AMDSPL_H
