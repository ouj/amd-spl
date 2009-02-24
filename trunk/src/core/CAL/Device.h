//
//
//
//  @ Project : AMD-SPL
//  @ File Name : Device.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//

#ifndef _DEVICE_H
#define _DEVICE_H

#include "cal.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Device
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
                CALdevice                   _deviceHandle;
                CALdeviceinfo               _deviceInfo;
                CALdeviceattribs            _deviceAttribs;
                CALdevicestatus             _deviceStatus;
                CALcontext                  _context;
                unsigned short              _Id;
				bool                        _shutDownOnDestroy;
            };
        }
    }
}

#endif  //_DEVICE_H
