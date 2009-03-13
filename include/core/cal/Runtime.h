#ifndef AMDSPL_RUNTIME_H
#define AMDSPL_RUNTIME_H

//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		Runtime.h
//!	\date 		27:2:2009   15:41
//!	\author		Jiawei OU
//!	
//!	\brief		Contain declaration of Runtime class.
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
			class DeviceManager;
			class BufferManager;
			class ProgramManager;
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	Runtime class is the core class of the SPL runtime, it manages
            //!         the initialization and shutdown of CAL. It also manages the 
            //!         creation and destruction of DeviceManager, BufferManager and 
            //!         ProgramManager. It is a singleton class. It destroyed when 
            //!         Runtime::destroy() is called or once application exits.
            //! 
            //! \warning Not thread safe! 
            //!
            //////////////////////////////////////////////////////////////////////////
            class SPL_EXPORT Runtime
            {
            public:
                static Runtime* getInstance();
                static void destroy();
                DeviceManager* getDeviceManager();
                BufferManager* getBufferManager();
                ProgramManager* getProgramManager();
            private:
				Runtime();
				~Runtime();
                bool virtual create();

                //! \brief	Pointer to the DeviceManager instance.
                DeviceManager* _deviceMgr;

                //! \brief	Pointer to the BufferManager instance.
                BufferManager* _bufferMgr;

                //! \brief	Pointer to the ProgramManager instance.
                ProgramManager* _programMgr;

                //! \brief  The singleton instance of Runtime class.
                static Runtime* _runtime;

                //! \brief  A boolean value set in initialization, indicate whether 
                //!         then the runtime should shutdown CAL when exit.
                bool _shutdownOnDestroy;
            };
        }
    }
}

#endif  //AMDSPL_RUNTIME_H
