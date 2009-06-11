//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		Program.cpp
//!	\date 		1:3:2009   15:28
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of Program class.
//!
//////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
#pragma warning(disable : 4996)
#endif
#include "CalCommonDefs.h"
#include "RuntimeDefs.h"
#include "CommonDefs.h"
#include "Program.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	device The pointer to the Device object this program 
            //!         associated to. 
            //! \return	Constructor
            //!
            //! \brief	Construct the Program object. The Program object will not be
            //!         available until Program::initialize() is called.
            //!
            //////////////////////////////////////////////////////////////////////////
            Program::Program(Device *device) : _device(device), _module(0), _func(0)
            {

            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy the Program object, unbind all the buffers and 
            //!         unload the program module.
            //!
            //////////////////////////////////////////////////////////////////////////
            Program::~Program()
            {
                // Destroy the module
                if(_module)
                {
                    // unbind all the buffers.
                    unbindAll();

                    CALcontext ctx = _device->getContext();

                    calModuleUnload(ctx, _module);
                }
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	progInfo Instance of ProgramInfo, contains program parameter
            //!         information, program ID and source
            //! \return	bool True if the Program object is successfully initialized.
            //!              False if the there is an error during initialization.
            //!
            //! \brief	Initialize the Program object. In this method, the IL source
            //!         provided in ProgramInfo will be compiled, linked and loaded 
            //!         onto CAL context of the device. Then, the module entry 
            //!         function handle and all the register names are retrieved.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Program::initialize(const ProgramInfo &progInfo)
            {
                if (!_device)
                {
                    return false;
                }

                CALdeviceinfo info = _device->getInfo();
                CALcontext ctx = _device->getContext();

                CALresult result;

                // Compiling program
                CALobject obj = 0;
                assert(progInfo.getSource());
                result = calclCompile(&obj, CAL_LANGUAGE_IL, progInfo.getSource(), info.target);
                CHECK_CAL_RESULT_ERROR(result, "Failed to compile program\n");

                // Linking program
                CALimage image;
                result = calclLink(&image, &obj, 1);
                CHECK_CAL_RESULT_ERROR(result, "Failed to create image\n");
                calclFreeObject(obj);

                // Load program
                result = calModuleLoad(&_module, ctx, image);
                CHECK_CAL_RESULT_ERROR(result, "Failed to load module\n");
                calclFreeImage(image);

                // Get function handle
                result = calModuleGetEntry(&_func, ctx, _module, "main");
                CHECK_CAL_RESULT_ERROR(result, "Failed to get function handle\n");

                char symbolStr[16];
                // Get constant name handle
                for(unsigned int i = 0; i < progInfo._constants; ++i)
                {
                    CALname name = 0;
                    sprintf(symbolStr, "cb%d", i);
                    result = calModuleGetName(&name, ctx, _module, symbolStr);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to get name handle for constants\n");

                    _constNames.push_back(name);
                }


                // Get all the input name handles
                for(unsigned int i = 0; i < progInfo._inputs; ++i)
                {
                    CALname name = 0;
                    sprintf(symbolStr, "i%d", i);
                    result = calModuleGetName(&name, ctx, _module, symbolStr);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to get name handle for input stream\n");

                    _inputNames.push_back(name);
                }

                // Get all the output name handles
                for(unsigned int i = 0; i < progInfo._outputs; ++i)
                {
                    CALname name = 0;
                    sprintf(symbolStr, "o%d", i);
                    result = calModuleGetName(&name, ctx, _module, symbolStr);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to get name handle for output stream\n");

                    _outputNames.push_back(name);
                }

                // Get name handle for scatter stream
                if(progInfo._global != 0)
                {
                    CALname name = 0;
                    result = calModuleGetName(&name, ctx, _module, "g[]");
                    CHECK_CAL_RESULT_ERROR(result, "Failed to get name handle for global stream\n");

                    _globalName = name;
                }

                // Initialize Buffer
                _constBuffers.resize(progInfo._constants);
                _inputBuffers.resize(progInfo._inputs);
                _outputBuffers.resize(progInfo._outputs);
                _globalBuffer = BufferItem();

                return true;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	buffer  The pointer to the input buffer to be bound
            //! \param	idx     The index of a program input register.
            //! \return	bool    True if the input buffer is successfully bound.
            //!                 False if an error happens during buffer binding.
            //!
            //! \brief	Bind a input buffer. If another buffer is already bound to 
            //!         this program input register, it will be unbound before the 
            //!         new input buffer is bound.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Program::bindInput(IBuffer* buffer, unsigned int idx)
            {
                assert(idx <= _inputBuffers.size());
                if (idx > _inputBuffers.size())
                {
                    LOG_ERROR("Input buffer out of range.\n");
                    return false;
                }
                unbindInput(idx);

                CALname name = getInputName(idx);
                CALcontext ctx = _device->getContext();
                CALresource res = buffer->getResHandle();
                CALmem mem;

                // Get the memory handle
                CALresult result = calCtxGetMem(&mem, ctx, res);
                CHECK_CAL_RESULT_ERROR(result, "Failed to get input memory handle \n");

                result = calCtxSetMem(ctx, name, mem);
                CHECK_CAL_RESULT_ERROR(result, "Failed to bind input memory\n");

                _inputBuffers[idx].buffer = buffer;
                _inputBuffers[idx].mem = mem;

                return true;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	buffer  The pointer to the output buffer to be bound
            //! \param	idx     The index of a program output register.
            //! \return	bool    True if the output buffer is successfully bound.
            //!                 False if an error happens during buffer binding.
            //!
            //! \brief	Bind a output buffer. If another buffer is already bound to 
            //!         this program output register, it will be unbound before the 
            //!         new output buffer is bound.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Program::bindOutput(IBuffer* buffer, unsigned int idx)
            {
                assert(idx <= _outputBuffers.size());
                if (idx > _outputBuffers.size())
                {
                    LOG_ERROR("Output buffer out of range.\n");
                    return false;
                }
                unbindOutput(idx);

                CALname name = getOutputName(idx);
                CALcontext ctx = _device->getContext();
                CALresource res = buffer->getResHandle();
                CALmem mem;

                // Get the memory handle
                CALresult result = calCtxGetMem(&mem, ctx, res);
                CHECK_CAL_RESULT_ERROR(result, "Failed to get output memory handle \n");

                result = calCtxSetMem(ctx, name, mem);
                CHECK_CAL_RESULT_ERROR(result, "Failed to bind output memory\n");

                _outputBuffers[idx].buffer = buffer;
                _outputBuffers[idx].mem = mem;

                return true;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	buffer  The pointer to the constant buffer to be bound
            //! \param	idx     The index of a program constant register.
            //! \return	bool    True if the constant buffer is successfully bound.
            //!                 False if an error happens during buffer binding.
            //!
            //! \brief	Bind a constant buffer. If another buffer is already bound to 
            //!         this program constant register, it will be unbound before the  
            //!         new constant buffer is bound.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Program::bindConstant(ConstBuffer* buffer, unsigned int idx)
            {
                assert(idx <= _constBuffers.size());
                if (idx > _constBuffers.size())
                {
                    LOG_ERROR("Constant buffer out of range.\n");
                    return false;
                }
                unbindConstant(idx);

                CALname name = getConstName(idx);
                CALcontext ctx = _device->getContext();
                CALresource res = buffer->getResHandle();
                CALmem mem;

                // Get the memory handle
                CALresult result = calCtxGetMem(&mem, ctx, res);
                CHECK_CAL_RESULT_ERROR(result, "Failed to get constant memory handle \n");

                result = calCtxSetMem(ctx, name, mem);
                CHECK_CAL_RESULT_ERROR(result, "Failed to bind constant memory\n");

                _constBuffers[idx].buffer = buffer;
                _constBuffers[idx].mem = mem;

                return true;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	buffer  The pointer to the global buffer to be bound
            //! \return	bool    True if the global buffer is successfully bound.
            //!                 False if an error happens during buffer binding.
            //!
            //! \brief	Bind a global buffer
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Program::bindGlobal(IBuffer* buffer)
            {
                if (!getGlobalName())
                {
                    LOG_ERROR("No global buffer.\n");
                    return false;
                }
 
                unbindGlobal();

                assert(buffer->isGlobal());
                if (!buffer->isGlobal())
                {
                    LOG_COMMON_ERROR("Cannot bind buffer which is not global to global name\n");
                    return false;
                }

                CALname name = getGlobalName();
                CALcontext ctx = _device->getContext();
                CALresource res = buffer->getResHandle();
                CALmem mem;

                // Get the memory handle
                CALresult result = calCtxGetMem(&mem, ctx, res);
                CHECK_CAL_RESULT_ERROR(result, "Failed to get global memory handle \n");

                result = calCtxSetMem(ctx, name, mem);
                CHECK_CAL_RESULT_ERROR(result, "Failed to bind global memory\n");

                _globalBuffer.buffer = buffer;
                _globalBuffer.mem = mem;

                return true;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	idx     The index of a program input register. 
            //! \return	bool    True if the input buffer is successfully unbound.
            //!                 False if an error happens during buffer unbinding.
            //!
            //! \brief	Unbind a input buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Program::unbindInput(unsigned int idx)
            {
                assert(idx <= _inputBuffers.size());
                if (idx > _inputBuffers.size())
                {
                    return false;
                }
                if (_inputBuffers[idx].buffer != 0)
                {
                    CALname name = getInputName(idx);
                    CALcontext ctx = _device->getContext();

                    CALresult result = calCtxSetMem(ctx, name, 0);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to unbind input memory\n");

                    // release mem handle
                    calCtxReleaseMem(_device->getContext(), _inputBuffers[idx].mem);
                    _inputBuffers[idx] = BufferItem();
                }

                return true;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	idx     The index of a program output register. 
            //! \return	bool    True if the output buffer is successfully unbound.
            //!                 False if an error happens during buffer unbinding.
            //!
            //! \brief	Unbind a output buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Program::unbindOutput(unsigned int idx)
            {
                assert(idx <= _outputBuffers.size());
                if (idx > _outputBuffers.size())
                {
                    return false;
                }
                if (_outputBuffers[idx].buffer != 0)
                {
                    CALname name = getOutputName(idx);
                    CALcontext ctx = _device->getContext();

                    CALresult result = calCtxSetMem(ctx, name, 0);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to unbind output memory\n");

                    // release mem handle
                    calCtxReleaseMem(_device->getContext(), _outputBuffers[idx].mem);
                    _outputBuffers[idx] = BufferItem();
                }
                return true;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	idx     The index of a program constant register. 
            //! \return	bool    True if the constant buffer is successfully unbound.
            //!                 False if an error happens during buffer unbinding.
            //!
            //! \brief	Unbind a constant buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Program::unbindConstant(unsigned int idx)
            {
                assert(idx <= _constBuffers.size());
                if (idx > _constBuffers.size())
                {
                    return false;
                }
                if (_constBuffers[idx].buffer != 0)
                {
                    CALname name = getConstName(idx);
                    CALcontext ctx = _device->getContext();

                    CALresult result = calCtxSetMem(ctx, name, 0);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to unbind constant memory\n");

                    // release mem handle
                    calCtxReleaseMem(_device->getContext(), _constBuffers[idx].mem);
                    _constBuffers[idx] = BufferItem();
                }
                return true;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool    True if the global buffer is successfully unbound.
            //!                 False if an error happens during buffer unbinding.
            //!
            //! \brief	Unbind a global buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Program::unbindGlobal()
            {
                if (_globalBuffer.buffer != 0)
                {
                    CALname name = getGlobalName();
                    CALcontext ctx = _device->getContext();

                    CALresult result = calCtxSetMem(ctx, name, 0);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to unbind constant memory\n");

                    // release mem handle
                    calCtxReleaseMem(_device->getContext(), _globalBuffer.mem);
                    _globalBuffer = BufferItem();
                }
                return false;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool    True if the all buffers are successfully unbound.
            //!                 False if at least one buffer failed to be unbound.
            //!
            //! \brief	Unbind all the buffers.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Program::unbindAll()
            {
                bool result = true;
                result = unbindGlobal() ? result : false;
                for (unsigned int idx = 0; idx < _constBuffers.size(); idx++)
                {
                    result = unbindConstant(idx) ? result : false;
                }
                for (unsigned int idx = 0; idx < _inputBuffers.size(); idx++)
                {
                    result = unbindInput(idx) ? result : false;
                }
                for (unsigned int idx = 0; idx < _outputBuffers.size(); idx++)
                {
                    result = unbindOutput(idx) ? result : false;
                }
                return result;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	Synchronize all the constant buffer. This method is usually 
            //!         called before the program execution.
            //!
            //////////////////////////////////////////////////////////////////////////
            void Program::syncConstBuffers(void)
            {
                for (unsigned int i = 0; i < _constBuffers.size(); i++)
                {
                    ConstBuffer* buffer = dynamic_cast<ConstBuffer*>(_constBuffers[i].buffer);
                    if (buffer)
                    {
                        if(!buffer->sync())
                        {
                            fprintf(stderr, "Failed to synchronize the constant buffer\n");
                        };
                    }
                } 
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	e       The pointer to the Event object contains the 
            //!                 execution event.
            //!
            //! \brief	Set the program execution event to all bound buffers.
            //!
            //////////////////////////////////////////////////////////////////////////
            void Program::setEvents(Event* e)
            {
                for (unsigned int idx = 0; idx < _constBuffers.size(); idx++)
                {
                    _constBuffers[idx].buffer->setInputEvent(e);
                }
                for (unsigned int idx = 0; idx < _inputBuffers.size(); idx++)
                {
                    _inputBuffers[idx].buffer->setInputEvent(e);
                }
                for (unsigned int idx = 0; idx < _outputBuffers.size(); idx++)
                {
                    _outputBuffers[idx].buffer->setOutputEvent(e);
                }
                if (_globalBuffer.buffer)
                {
                    _globalBuffer.buffer->setInputEvent(e); 
                    _globalBuffer.buffer->setOutputEvent(e);   
                }
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	Wait until all events of bound buffers are finish to prevent
            //!         data corruption. It is usually called before function execution.
            //!
            //////////////////////////////////////////////////////////////////////////
            void Program::waitEvents()
            {
                // Comment the const buffer and global buffer, will not be necessary now.
                //for (unsigned int idx = 0; idx < _constBuffers.size(); idx++)
                //{
                //    _constBuffers[idx].buffer->waitOutputEvent();
                //}
                for (unsigned int idx = 0; idx < _inputBuffers.size(); idx++)
                {
                    _inputBuffers[idx].buffer->waitOutputEvent();
                }
                for (unsigned int idx = 0; idx < _outputBuffers.size(); idx++)
                {
                    _outputBuffers[idx].buffer->waitInputEvent();
                }
                if (_globalBuffer.buffer)
                {
                    // global buffer maybe input too.
                    _globalBuffer.buffer->waitOutputEvent();
                    _globalBuffer.buffer->waitInputEvent();
                }
            }
        }
    }
}
