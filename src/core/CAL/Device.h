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
                Device(unsigned short id = 0);
                Device(unsigned short id, CALdevice device = 0);
                ~Device();
                bool initialize();
                CALdevice getHandle();
                CALdeviceinfo getInfo();
                CALdeviceattribs getAttribs();
                CALcontext getContext();
                unsigned short getId();
            private:
                CALdevice _deviceHandle;
                CALdeviceinfo _deviceInfo;
                CALdeviceattribs _deviceAttribs;
                CALcontext _context;
                unsigned short _Id;
				bool _shutDownOnDestroy;
            };
        }
    }
}

#endif  //_DEVICE_H
