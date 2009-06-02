#include "CounterManager.h"
#include "PerfCounter.h"
#include "CommonDefs.h"
#include "RuntimeDefs.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {

            PFNCALCTXDESTROYCOUNTER calCtxDestroyCounterExt;
            PFNCALCTXBEGINCOUNTER   calCtxBeginCounterExt;
            PFNCALCTXENDCOUNTER     calCtxEndCounterExt;
            PFNCALCTXGETCOUNTER     calCtxGetCounterExt;
            PFNCALCTXCREATECOUNTER  calCtxCreateCounterExt;

            CounterManager::CounterManager() 
            {

            }

            CounterManager::~CounterManager()
            {
            }

            bool CounterManager::initialize()
            {
                //////////////////////////////////////////////////////////////////////////
                //
                //  Get extension functions
                //
                if (calExtSupported((CALextid)CAL_EXT_COUNTERS) != CAL_RESULT_OK)
                {
                    LOG_ERROR("CAL do not support counters.\n");
                    return false;
                }

                if (calExtGetProc((CALextproc*)&calCtxCreateCounterExt, (CALextid)CAL_EXT_COUNTERS, "calCtxCreateCounter"))
                {
                    LOG_ERROR("calCtxCreateCounter is not supported\n");
                    return false;
                }

                if (calExtGetProc((CALextproc*)&calCtxDestroyCounterExt, (CALextid)CAL_EXT_COUNTERS, "calCtxDestroyCounter"))
                {
                    LOG_ERROR("calCtxDestroyCounter is not supported\n");
                    return false;
                }

                if (calExtGetProc((CALextproc*)&calCtxBeginCounterExt, (CALextid)CAL_EXT_COUNTERS, "calCtxBeginCounter"))
                {
                    LOG_ERROR("calCtxBeginCounter is not supported\n");
                    return false;
                }

                if (calExtGetProc((CALextproc*)&calCtxEndCounterExt, (CALextid)CAL_EXT_COUNTERS, "calCtxEndCounter"))
                {
                    LOG_ERROR("calCtxEndCounter is not supported\n");
                    return false;
                }

                if (calExtGetProc((CALextproc*)&calCtxGetCounterExt, (CALextid)CAL_EXT_COUNTERS, "calCtxGetCounter"))
                {
                    LOG_ERROR("calCtxGetCounter is not supported\n");
                    return false;
                }
                return true;
            }

            PerfCounter *CounterManager::createGPUCounter(Device *device)
            {
                assert(device);
                if (!device)
                {
                    return NULL;
                }
                PerfCounter *gpu_counter = new PerfCounter(device);
                if (gpu_counter)
                {
                    if (!gpu_counter->initialize())
                    {
                        SAFE_DELETE(gpu_counter);
                    }
                }
                return gpu_counter;
            }

            bool CounterManager::destroyGPUCounter(PerfCounter *counter)
            {
                SAFE_DELETE(counter);
                return true;
            }
        }
    }
}

