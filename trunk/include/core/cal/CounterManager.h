#ifndef AMDSPL_COUNTER_MANAGER_H
#define AMDSPL_COUNTER_MANAGER_H

#include "cal.h"
#include "calcl.h"
#include "cal_ext.h"
#include "cal_ext_counter.h"
#include "Device.h"
#include "SplDefs.h"
#include "SPLCounter.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Device;
            class SPLCounter;
            class SPL_EXPORT CounterManager 
            {
                //friend class Runtime;
                public:
                    CounterManager();
                    ~CounterManager();
                    bool initialize();
                    SPLCounter *createGPUCounter(Device *device);
                    bool destroyGPUCounter(SPLCounter *counter);
            };
        }
    }
}

#endif
