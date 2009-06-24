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
            class SPL_EXPORT PerfCounter 
            {
                friend class CounterManager;
            protected:
                PerfCounter(Device *device);
            public:
                ~PerfCounter();
                bool initialize();
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
