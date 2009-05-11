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
#include "VectorDataType.h"
#include "ProgramInfo.h"
#include <vector>
#include <utility>
#include <stdio.h>
#include "calcl.h"


using namespace std;

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief      ProgExeInfo class contains the execution information of
            //!             a program. For general program, it is cal domain. For
            //!             compute program, it is execution grid information.
            //!	
            //!	\author     Jiawei Ou
            //!
            //////////////////////////////////////////////////////////////////////////
            union SPL_EXPORT ProgExeInfo
            {
                ProgExeInfo(uint4 domain)
                {
                    this->domain = domain;
                };
                ProgExeInfo(CALuint flags, uint3 gridBlock, uint3 gridSize)
                {
                    this->flags = flags;
                    this->gridBlock = gridBlock;
                    this->gridSize = gridSize;
                };
                struct  
                {
                    uint4   domain;
                };
                struct  
                {
                    CALuint flags;
                    uint3   gridBlock;
                    uint3   gridSize;
                };
            };

            class IBuffer;
            class ConstBuffer;
            class IGlobalBuffer;

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
                BufferItem() : buffer(0), mem(0) {}
                //! \brief	The pointer to the Buffer object bound to the Program.
                IBuffer* buffer;
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
                bool            initialize(const ProgramInfo &progInfo);
                //////////////////////////////////////////////////////////////////////////
                //!
                //! \param	exeInfo
                //!
                //! \brief	Set the execution information of the program. For general 
                //!         program, it is cal domain. For compute program, it is 
                //!         execution grid information.
                //!
                //////////////////////////////////////////////////////////////////////////
                virtual void    setExeInfo(const ProgExeInfo &exeInfo) = 0;
                //////////////////////////////////////////////////////////////////////////
                //!
                //! \return	Event* The event of the execution.
                //!
                //! \brief	Execute the program.
                //!
                //////////////////////////////////////////////////////////////////////////
                virtual Event*  run() = 0;
                bool            bindInput(IBuffer* buffer, unsigned int idx);
                bool            bindOutput(IBuffer* buffer, unsigned int idx);
                bool            bindConstant(ConstBuffer* buffer, unsigned int idx);
                bool            bindGlobal(IBuffer* buffer);

                bool            unbindInput(unsigned int idx);
                bool            unbindOutput(unsigned int idx);
                bool            unbindConstant(unsigned int idx);
                bool            unbindGlobal();
                bool            unbindAll();

                inline Device*  getDevice() const;
                inline CALfunc  getFunction() const;
                inline CALname  getOutputName(unsigned short i) const;
                inline CALname  getInputName(unsigned short i) const;
                inline CALname  getConstName(unsigned short i) const;
                inline CALname  getGlobalName() const;
            protected:
                void            syncConstBuffers(void);
                void            setEvents(Event* e);
                void            waitEvents(void);
                //! \brief	The pointer to the Device object this program associated to.
                Device*                 _device;
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

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Device* Pointer to the device of the program.
            //!
            //! \brief	Get the device of the program.
            //!
            //////////////////////////////////////////////////////////////////////////
            inline Device* Program::getDevice() const
            {
                return _device;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CALfunc The handle of IL function.
            //!
            //! \brief	Get CAL IL function handle.
            //!
            //////////////////////////////////////////////////////////////////////////
            inline CALfunc Program::getFunction() const
            {
                return _func;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	i       The index of the output register.
            //! \return	CALname The CAL name of the output register.
            //!
            //! \brief	Get CAL name of a output register.
            //!
            //////////////////////////////////////////////////////////////////////////
            inline CALname Program::getOutputName(unsigned short i) const
            {
                assert(i <= _outputNames.size());
                return _outputNames[i];
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	i       The index of the input register.
            //! \return	CALname The CAL name of the input register.
            //!
            //! \brief	Get CAL name of a input register.
            //!
            //////////////////////////////////////////////////////////////////////////
            inline CALname Program::getInputName(unsigned short i) const
            {
                assert(i <= _inputNames.size());
                return _inputNames[i];
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	i       The index of the constant register.
            //! \return	CALname The CAL name of the constant register.
            //!
            //! \brief	Get CAL name of a constant register.
            //!
            //////////////////////////////////////////////////////////////////////////
            inline CALname Program::getConstName(unsigned short i) const
            {
                assert(i <= _constNames.size());
                return _constNames[i];
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CALname The CAL name of the global register.
            //!
            //! \brief	Get CAL name of a global register.
            //!
            //////////////////////////////////////////////////////////////////////////
            inline CALname Program::getGlobalName() const
            {
                return _globalName;
            }
        }
    }
}

#endif  //AMDSPL_PROGRAM_H
