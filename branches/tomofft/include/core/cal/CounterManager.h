#ifndef AMDSPL_COUNTER_MANAGER_H
#define AMDSPL_COUNTER_MANAGER_H

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
            class PerfCounter;
            class SPL_EXPORT CounterManager 
            {
            public:
                CounterManager();
                ~CounterManager();
                bool initialize();
                PerfCounter *createGPUCounter(Device *device);
                bool destroyGPUCounter(PerfCounter *counter);
            };
        }
    }
}

#endif
