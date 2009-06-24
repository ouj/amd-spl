#include "RuntimeDefs.h"
#include "PerfCounter.h"
#include "CommonDefs.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            extern PFNCALCTXDESTROYCOUNTER calCtxDestroyCounterExt;
            extern PFNCALCTXBEGINCOUNTER   calCtxBeginCounterExt;
            extern PFNCALCTXENDCOUNTER     calCtxEndCounterExt;
            extern PFNCALCTXGETCOUNTER     calCtxGetCounterExt;
            extern PFNCALCTXCREATECOUNTER  calCtxCreateCounterExt;

            PerfCounter::PerfCounter(Device *device) : _device(device)
            {
            }

            bool PerfCounter::initialize()
            {
                if (!_device)
                {
                    return false;
                }

                if (calCtxCreateCounterExt(&_idleCounter, _device->getContext() , CAL_COUNTER_IDLE) != CAL_RESULT_OK)
                {
                    LOG_ERROR("IDLE Counter is not supported\n");
                    return false;
                }

                if (calCtxCreateCounterExt(&_cacheCounter, _device->getContext(), CAL_COUNTER_INPUT_CACHE_HIT_RATE) != CAL_RESULT_OK)
                {
                    LOG_ERROR("CACHE Counter is not supported\n");
                    return false;
                }
                return true;
            }

            PerfCounter::~PerfCounter()
            {
                Device *device = this->getDeviceHandle();
                if (calCtxDestroyCounterExt(device->getContext(), _idleCounter) != CAL_RESULT_OK)
                {
                    LOG_ERROR("IDLE Counter can NOT be destroyed\n");
                }

                if (calCtxDestroyCounterExt(device->getContext(), _cacheCounter) != CAL_RESULT_OK)
                {
                    LOG_ERROR("CACHE Counter can NOT be destroyed\n");
                }
            }

            bool PerfCounter::reset()
            {
                LOG_ERROR("reset is not supported now!\n");
                return false;
            }

            bool PerfCounter::start()
            {
                if (calCtxBeginCounterExt(_device->getContext(), _idleCounter) != CAL_RESULT_OK)
                {
                    LOG_ERROR("IDLE Counter can NOT start\n");
                    return false;
                }

                if (calCtxBeginCounterExt(_device->getContext(), _cacheCounter) != CAL_RESULT_OK)
                {
                    LOG_ERROR("CACHE Counter can NOT start\n");
                    return false;
                }

                return true;
            }

            bool PerfCounter::stop()
            {
                if (calCtxEndCounterExt(_device->getContext(), _idleCounter) != CAL_RESULT_OK)
                {
                    LOG_ERROR("IDLE Counter can NOT stop\n");
                    return false;
                }

                if (calCtxEndCounterExt(_device->getContext(), _cacheCounter) != CAL_RESULT_OK)
                {
                    LOG_ERROR("CACHE Counter can NOT stop\n");
                    return false;
                }

                return true;
            }

            void PerfCounter::printCounter()
            {
                CALfloat idlePercentage = 0.0f;
                CALfloat cachePercentage = 0.0f;
                if (calCtxGetCounterExt(&idlePercentage, _device->getContext(), _idleCounter) != CAL_RESULT_OK)
                {
                    LOG_ERROR("Can NOT IDLE Counter value\n");
                }
                if (calCtxGetCounterExt(&cachePercentage, _device->getContext(), _cacheCounter) != CAL_RESULT_OK)
                {
                    LOG_ERROR("Can NOT CACHE Counter value\n");
                }
                printf("SIMD idel percentage : %1.4f, cache hit percentage : %1.4f", idlePercentage, cachePercentage);
            }

            Device *PerfCounter::getDeviceHandle() {
                return _device;
            }
        }
    }
}

