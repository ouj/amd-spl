#include "RuntimeDefs.h"
#include "SPLCounter.h"
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

            SPLCounter::SPLCounter(Device *device) : _device(device)
            {
                if (calCtxCreateCounterExt(&_idleCounter, device->getContext() , CAL_COUNTER_IDLE) != CAL_RESULT_OK)
                {
                    LOG_ERROR("IDLE Counter is not supported\n");
                }

                if (calCtxCreateCounterExt(&_cacheCounter, device->getContext(), CAL_COUNTER_INPUT_CACHE_HIT_RATE) != CAL_RESULT_OK)
                {
                    LOG_ERROR("CACHE Counter is not supported\n");
                }
            }

            SPLCounter::~SPLCounter()
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

            bool SPLCounter::reset()
            {
                LOG_ERROR("reset is not supported now!\n");
                return false;
            }

            bool SPLCounter::start()
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

            bool SPLCounter::stop()
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

            void SPLCounter::printCounter()
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

            Device *SPLCounter::getDeviceHandle() {
                return _device;
            }
        }
    }
}

