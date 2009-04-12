//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		Event.cpp
//!	\date 		1:3:2009   13:40
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of Event class.
//!
//////////////////////////////////////////////////////////////////////////
#include "Event.h"
#include "RuntimeDefs.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Constructor
            //!
            //! \brief	Construct the Event object, reset the Event object to unused.
            //!
            //////////////////////////////////////////////////////////////////////////
            Event::Event()
            {
                reset();
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	e   The CAL event handle.
            //! \param	ctx The CAL context handle.
            //! \return	void
            //!
            //! \brief	Set the CAL event handle and CAL context handle.
            //!
            //////////////////////////////////////////////////////////////////////////
            void Event::set(CALevent e, CALcontext ctx)
            {
                _event = e;
                _ctx = ctx;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool True if the object is not being used by any buffer or 
            //!              program. False if the object is being used.
            //!
            //! \brief	Check if the Event object is unused.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Event::isUnused()
            {
                return (!_event || !_ctx);
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CALevent The CAL event handle.
            //!
            //! \brief	Get the CAL event handle.
            //!
            //////////////////////////////////////////////////////////////////////////
            CALevent Event::getHandle()
            {
                return _event;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CALcontext The CAL context handle.
            //!
            //! \brief	Get the CAL context handle.
            //!
            //////////////////////////////////////////////////////////////////////////
            CALcontext Event::getContext()
            {
                return _ctx;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	Reset the event to unused.
            //!
            //////////////////////////////////////////////////////////////////////////
            void Event::reset()
            {
                _event = 0;
                _ctx = 0;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	Wait until the event is done, then reset the Event object to
            //!         unused.
            //!
            //////////////////////////////////////////////////////////////////////////
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

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CALresult The CAL event status.
            //!
            //! \brief	Check if the event status.
            //!
            //////////////////////////////////////////////////////////////////////////
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
