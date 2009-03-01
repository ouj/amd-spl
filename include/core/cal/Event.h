#if !defined(_EVENT_H)
#define _EVENT_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		Event.h
//!	\date 		1:3:2009   13:39
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of Event class.
//!
//////////////////////////////////////////////////////////////////////////
#include "cal.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	Event class is an abstract representation of CAL event. 
            //!         It contains method for event checking and event waiting.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
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
                //! \brief	Stores the CAL event handle.
                CALevent    _event;
                //! \brief	Stores the CAL device context the event handle associated to.
                CALcontext  _ctx;
            };
        }
    }
}

#endif  //_EVENT_H
