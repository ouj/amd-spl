#ifndef AMDSPL_SPLCOUNTER_H
#define AMDSPL_SPLCOUNTER_H

#include "cal.h"
#include "calcl.h"
#include "cal_ext.h"
#include "cal_ext_counter.h"
#include "Device.h"
#include "SplDefs.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Device;
            class SPL_EXPORT SPLCounter {
                public:
                    SPLCounter(Device *device);
                    ~SPLCounter();
                    bool reset();
                    bool start();
                    bool stop();
                    void printCounter();
                    Device *getDeviceHandle();
                private:
                    CALcounter _idleCounter;
                    CALcounter _cacheCounter;
                    Device *_device;
            };
        }
    }
}

#endif
