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
                friend class Program;
                friend class ProgramManager;
            public:
                Event();
                void        set(CALevent e, CALcontext ctx);
                void        reset();
                bool        isUnused();
                CALevent    getHandle();
                CALcontext  getContext();
                void        waitEvent();
                CALresult   checkEvent();
            private:
                CALevent    _event;
                CALcontext  _ctx;
            };
        }
    }
}

#endif  //_EVENT_H