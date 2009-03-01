#if !defined(_AMDSPL_H)
#define _AMDSPL_H

//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		amdspl.h
//!	\date 		27:2:2009   16:43
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of the initialization function and cleanup 
//!        function. it also include headers that are necessary to run the SPL 
//!
//////////////////////////////////////////////////////////////////////////
#include "cal.h"
#include "SPLDefs.h"

#ifdef AMD_SPL_EXPORT
#define SPL_EXPORT __declspec(dllexport)
#else
#define SPL_EXPORT
#endif

namespace amdspl
{
    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief DEVICE_LIST_ITEM defines a item in device list. Used in 
    //!        AmdSpl::InitializeSPL to indicate which devices are available 
    //!        in AMD-SPL
    //!
    //////////////////////////////////////////////////////////////////////////
	struct SPL_EXPORT DEVICE_LIST_ITEM
	{
	public:
		DEVICE_LIST_ITEM(unsigned short deviceId = 0, CALdevice deviceHandle = 0);
        //! \brief	The device ID of the device will be used in AMD-SPL.
		unsigned short deviceId;
        //! \brief	The device handle of the device will be used in AMD-SPL.
		CALdevice deviceHandle;
	};

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief	AmdSpl class, manages the initialization and destruction of AMD-SPL.
    //!
    //////////////////////////////////////////////////////////////////////////
    class SPL_EXPORT AmdSpl
    {
    public:
        static SPL_RESULT InitializeSPL(DEVICE_LIST_ITEM *devices = 0, unsigned short numDevices = 0, int defaultDeviceIdx = 0);
        static SPL_RESULT CleanupSPL();
    };
}

#endif  //_AMDSPL_H
