#if !defined(_PROGRAMMANAGER_H)
#define _PROGRAMMANAGER_H

//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		ProgramManager.h
//!	\date 		27:2:2009   22:16
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of ProgramManager class.
//!
//////////////////////////////////////////////////////////////////////////
#include "Program.h"
#include "CommonDefs.h"
#include <vector>

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	The ProgramManager contains load and unload methods for 
            //!         Program. It also contains an event pool which can be used in
            //!         event management. It is created when the runtime is 
            //!         initialized and deleted when the runtime is destroyed.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class ProgramManager
            {
                friend class Runtime;
            public:
                template<typename ProgInfo>
                Program*    loadProgram(const ProgInfo &progInfo, Device* device = NULL);
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

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \tparam ProgInfo Template type of the ProgramInfo, contains program 
            //!                  parameter information.
            //! \param	progInfo The ProgramInfo object contains source code and 
            //!                  program ID.
            //! \param	device   The pointer to the Device.The method will be compiled
            //!                  based on this device target and load it onto its 
            //!                  context.
            //! \return	Program* The pointer to the Program object if the program is
            //!                  successfully loaded. NULL is there is an error during
            //!                  loading the program.
            //!
            //! \brief	Compile the program base on the device target and load it onto 
            //!         the corresponding device context. The program information is 
            //!         provided in a ProgramInfo object.
            //!
            //////////////////////////////////////////////////////////////////////////
            template<typename ProgInfo>
            Program* ProgramManager::loadProgram(const ProgInfo &progInfo, Device* device)
            {
                if (device == NULL)
                {
                    // use the default device;
                    device = 
                        Runtime::getInstance()->getDeviceManager()->getDefaultDevice();
                }

                Program *prog = new Program(device);
                if (!prog->initialize(progInfo))
                {
                    SAFE_DELETE(prog);
                    return NULL;
                }
                return prog;
            }
        }
    }
}
#endif  //_PROGRAMMANAGER_H
