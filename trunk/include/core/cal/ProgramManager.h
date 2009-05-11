#ifndef AMDSPL_PROGRAMMANAGER_H
#define AMDSPL_PROGRAMMANAGER_H

//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		ProgramManager.h
//!	\date 		27:2:2009   22:16
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of ProgramManager class.
//!
//////////////////////////////////////////////////////////////////////////
#include "SplDefs.h"
#include "ProgramInfo.h"

#include <vector>

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Device;
            class Event;
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	ProgramManager class contains load and unload methods for 
            //!         Program. It also contains an event pool which can be used in
            //!         event management. It is created when the runtime is 
            //!         initialized and deleted when the runtime is destroyed.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class SPL_EXPORT ProgramManager
            {
                friend class Runtime;
            public:
                Program*    loadProgram(const ProgramInfo& progInfo, Device* device = NULL);
                void        unloadProgram(Program* program);
                Event*      getEvent();
            protected:
                            ProgramManager();
                            ~ProgramManager();
                bool        initialize();
            private:
                //! \brief	The event pool.
                vector<Event*>  _eventPool;
            };
        }
    }
}

#endif  //AMDSPL_PROGRAMMANAGER_H
