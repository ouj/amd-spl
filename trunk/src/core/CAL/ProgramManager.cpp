//
//
//
//  @ Project : AMD-SPL
//  @ File Name : ProgramManager.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#include "ProgramManager.h"
#include "Program.h"
#include "CommonDefs.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	program Pointer of the Program object to unload.
            //!
            //! \brief	Unload a program, release its resource.
            //!
            //////////////////////////////////////////////////////////////////////////
            void ProgramManager::unloadProgram(Program* program)
            {
                SAFE_DELETE(program);
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Constructor
            //!
            //! \brief	Construct a ProgramManager object. It will not be available
            //!         until ProgramManager::initialize() is called.
            //!
            //////////////////////////////////////////////////////////////////////////
            ProgramManager::ProgramManager()
            {
            
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy a ProgramManager object.
            //!
            //////////////////////////////////////////////////////////////////////////
            ProgramManager::~ProgramManager()
            {
                for(unsigned int i = 0; i < _eventPool.size(); ++i)
                {
                    SAFE_DELETE(_eventPool[i]);
                }
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool True if the ProgramManager is successfully initialized.
            //!              False if there is an error during the initialization.
            //!
            //! \brief	Initialize the ProgramManager.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool ProgramManager::initialize()
            {
                return true;
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Event* The pointer to an unused event.
            //!
            //! \brief	Get an unused event from the event pool
            //!
            //////////////////////////////////////////////////////////////////////////
            Event* ProgramManager::getEvent()
            {
                // Look for a free event in the cache
                for(unsigned int i = 0; i < _eventPool.size(); ++i)
                {
                    if(_eventPool[i]->isUnused())
                    {
                        return _eventPool[i];
                    }
                }
                // Create if not found
                Event* e = new Event();
                _eventPool.push_back(e);
                return e;
            }
        }
    }
}
