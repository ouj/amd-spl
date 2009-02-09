//
//
//
//  @ Project : AMD-SPL
//  @ File Name : Event.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_EVENT_H)
#define _EVENT_H
#include "cal.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Event
            {
            public:
                Event(CALevent event);
                void getHandle();
                void waitEvent();
                void checkEvent();
            private:
                CALevent _event;
                CALcontext _context;
            };
        }
    }
}

#endif  //_EVENT_H
