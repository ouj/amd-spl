#ifndef AMDSPL_PROGRAM_H
#define AMDSPL_PROGRAM_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		Program.h
//!	\date 		1:3:2009   14:08
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of Program class.
//!
//////////////////////////////////////////////////////////////////////////
#include "Event.h"
#include "Device.h"
#include "SplDefs.h"
#include <vector>
#include <utility>
#include <stdio.h>
#include "calcl.h"
#include "CommonDefs.h"

using namespace std;

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Buffer;
            class ConstBuffer;
            class GlobalBuffer;

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief BufferItem class is consist of a pointer to the Buffer 
            //!        object and a CALmem handle. It is used by Program class. 
            //! \warning Internal use only.
            //!
            //////////////////////////////////////////////////////////////////////////
            struct BufferItem
            {
                
                //////////////////////////////////////////////////////////////////////////
                //!
                //! \return	Constructor.
                //!
                //! \brief	Construct the BufferItem object. Set all its members to 0.
                //!
                //////////////////////////////////////////////////////////////////////////
                BufferItem() : buffer(NULL), mem(0) {}
                //! \brief	The pointer to the Buffer object bound to the Program.
                Buffer* buffer;
                //! \brief	The CAL memory handle of the buffer.
                CALmem  mem;
            };

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	Program class is an abstract representation of CAL program.  
            //!         It contains methods for program initialization, including  
            //!         compiling, linking and loading. It also provides methods for 
            //!         buffer binding, program execution and event handling.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class SPL_EXPORT Program
            {
            public:
                                Program(Device *device);
                                ~Program();
                template<typename ProgInfo>
                bool            initialize(const ProgInfo &progInfo);
                virtual Event*  run(const CALdomain &domain);
                bool            bindInput(Buffer* buffer, unsigned int idx);
                bool            bindOutput(Buffer* buffer, unsigned int idx);
                bool            bindConstant(ConstBuffer* buffer, unsigned int idx);
                bool            bindGlobal(GlobalBuffer* buffer);

                bool            unbindInput(unsigned int idx);
                bool            unbindOutput(unsigned int idx);
                bool            unbindConstant(unsigned int idx);
                bool            unbindGlobal();
                bool            unbindAll();

                inline CALname  getOutputName(unsigned short i) const;
                inline CALname  getInputName(unsigned short i) const;
                inline CALname  getConstName(unsigned short i) const;
                inline CALname  getGlobalName() const;
            private:
                void            syncConstBuffers(void);
                void            setEvents(Event* e);
                void            waitEvents(void);
                //! \brief	The pointer to the Device object this program associated to.
                Device*                 _device;
            private:
                //! \brief	CAL names of input buffers.
                vector<CALname>         _inputNames;
                //! \brief	CAL names of output buffers.
                vector<CALname>         _outputNames;
                //! \brief	CAL names of constant buffers.
                vector<CALname>         _constNames;
                //! \brief	CAL name of a global buffer.
                CALname                 _globalName;

                //! \brief	List of input buffers bound to this program.
                vector<BufferItem>      _inputBuffers;
                //! \brief	List of output buffers bound to this program.
                vector<BufferItem>      _outputBuffers;
                //! \brief	List of constant buffers bound to this program.
                vector<BufferItem>      _constBuffers;
                //! \brief	global buffer bound to this program.
                BufferItem              _globalBuffer;

                //! \brief	Stores the CAL function handle of this program.
                CALfunc                 _func;
                //! \brief	Stores the CAL module handle of this program.
                CALmodule               _module;
            };
        }
    }
}

#include "ProgramDefs.h"

#endif  //AMDSPL_PROGRAM_H
