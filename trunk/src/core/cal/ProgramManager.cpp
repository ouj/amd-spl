//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		ProgramManager.cpp
//!	\date 		1:3:2009   15:28
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of ProgramManager class.
//!
//////////////////////////////////////////////////////////////////////////
#include "ProgramManager.h"
#include "Runtime.h"
#include "DeviceManager.h"
#include "GeneralProgram.h"
#include "ComputeProgram.h"
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
            //! \param	progInfo The ProgramInfo object contains parameter information,
            //!                  source code and program ID.
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
            Program* ProgramManager::loadProgram(const ProgramInfo &progInfo, Device* device)
            {
                if (device == NULL)
                {
                    // use the default device;
                    device = 
                        Runtime::getInstance()->getDeviceManager()->getDefaultDevice();
                }

                Program *prog = NULL;
                if (progInfo._isCS)
                    prog = new ComputeProgram(device);
                else
                    prog = new GeneralProgram(device);
                
                if (!prog->initialize(progInfo))
                {
                    if(prog)
                    {
                        delete prog;
                        prog = NULL;
                    };
                    return NULL;
                }
                return prog;
            }

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
