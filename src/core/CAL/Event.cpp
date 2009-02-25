//
//
//
//  @ Project : AMD-SPL
//  @ File Name : Event.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#include "Event.h"
#include "RuntimeDefs.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            Event::Event()
            {
                reset();
            }

            void Event::set(CALevent e, CALcontext ctx)
            {
                _event = e;
                _ctx = ctx;
            }

            bool Event::isUnused()
            {
                return (!_event || !_ctx);
            }

            CALevent Event::getHandle()
            {
                return _event;
            }

            CALcontext Event::getContext()
            {
                return _ctx;
            }

            void Event::reset()
            {
                _event = 0;
                _ctx = 0;
            }

            void Event::waitEvent()
            {
                CALresult result;
                if (isUnused())
                    return;

                do 
                {
                    result = calCtxIsEventDone(_ctx, _event);
                    if (result == CAL_RESULT_ERROR)
                    {
                        reset();
                        return;
                    }
                } while (result == CAL_RESULT_PENDING);
                reset();
            }

            CALresult Event::checkEvent()
            {
                if (!isUnused())
                {
                    CALresult result = calCtxIsEventDone(_ctx, _event);
                    if (result != CAL_RESULT_PENDING)
                    {
                        reset();
                        return result;
                    }
                }
                return CAL_RESULT_BAD_HANDLE;
            }
        }
    }
}
