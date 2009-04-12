#ifndef AMDSPL_EVENT_H
#define AMDSPL_EVENT_H
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
#include "SplDefs.h"

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
            class SPL_EXPORT Event
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

#endif  //AMDSPL_EVENT_H
