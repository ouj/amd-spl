#ifndef _DEVICE_H
#define _DEVICE_H

//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		Device.h
//!	\date 		28:2:2009   21:56
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of Device class.
//!
//////////////////////////////////////////////////////////////////////////

#include "cal.h"
#include "SplDefs.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	Device class is an abstract representation of a CAL 
            //!         device in the system. It provides methods for device 
            //!         management, device information. 
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class SPL_EXPORT Device
            {
            public:
                Device(unsigned short id, CALdevice device = 0);
                ~Device();
                bool                        initialize();
                CALdevice                   getHandle();
                const CALdeviceinfo&        getInfo();
                const CALdeviceattribs&     getAttribs();
                const CALdevicestatus&      getStatus();
                CALcontext                  getContext();
                unsigned short              getId();
                bool                        flush();
            private:
                //! \brief	Stores the CAL handle of the device.
                CALdevice                   _deviceHandle;
                //! \brief	Stores the device information.
                CALdeviceinfo               _deviceInfo;
                //! \brief	Stores the device attributes.
                CALdeviceattribs            _deviceAttribs;
                //! \brief	Stores the device status.
                CALdevicestatus             _deviceStatus;
                //! \brief	Stores the handle of the context associated to the device.
                CALcontext                  _context;
                //! \brief	Stores the device ID.
                unsigned short              _Id;
                //! \brief	A boolean flag indicate whether the CAL device should be 
                //!         shutdown when Device object is destroyed.
				bool                        _shutDownOnDestroy;
            };
        }
    }
}

#endif  //_DEVICE_H
