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
            Event::Event(CALevent event, CALcontext ctx)
            {
                assert(event);
                _event = event;
                _ctx = ctx;
            }
            CALevent Event::getHandle()
            {
                return _event;
            }
            
            void Event::waitEvent()
            {
                while(calCtxIsEventDone(_ctx, _event));
            }

            CALresult Event::checkEvent()
            {
                return calCtxIsEventDone(_ctx, _event);
            }
        }
    }
}
