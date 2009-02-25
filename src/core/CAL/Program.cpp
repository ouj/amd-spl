//
//
//
//  @ Project : AMD-SPL
//  @ File Name : Program.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//

#include "RuntimeDefs.h"
#include "Program.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            Program::Program(Device *device) : _device(device), _module(0), _func(0)
            {

            }

            Program::~Program()
            {
                // unbind all the buffers.
                unbindAll();

                CALcontext ctx = _device->getContext();

                // Destroy the module
                if(_module)
                {
                    calModuleUnload(ctx, _module);
                }
            }

            bool Program::bindInput(Buffer* buffer, unsigned int idx)
            {
                assert(idx <= _inputBuffers.size());
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

            bool Program::bindOutput(Buffer* buffer, unsigned int idx)
            {
                assert(idx <= _outputBuffers.size());
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

            bool Program::bindConstant(ConstBuffer* buffer, unsigned int idx)
            {
                assert(idx <= _constBuffers.size());
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

            bool Program::bindGlobal(GlobalBuffer* buffer)
            {
                unbindGlobal();

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

            bool Program::unbindInput(unsigned int idx)
            {
                assert(idx <= _inputBuffers.size());
                if (_inputBuffers[idx].buffer != NULL)
                {
                    CALname name = getInputName(idx);
                    CALcontext ctx = _device->getContext();

                    CALresult result = calCtxSetMem(ctx, name, NULL);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to unbind input memory\n");

                    // release mem handle
                    calCtxReleaseMem(_device->getContext(), _inputBuffers[idx].mem);
                    _inputBuffers[idx] = BufferItem();
                }

                return true;
            }

            bool Program::unbindOutput(unsigned int idx)
            {
                assert(idx <= _outputBuffers.size());
                if (_outputBuffers[idx].buffer != NULL)
                {
                    CALname name = getOutputName(idx);
                    CALcontext ctx = _device->getContext();

                    CALresult result = calCtxSetMem(ctx, name, NULL);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to unbind output memory\n");

                    // release mem handle
                    calCtxReleaseMem(_device->getContext(), _outputBuffers[idx].mem);
                    _outputBuffers[idx] = BufferItem();
                }
                return true;
            }

            bool Program::unbindConstant(unsigned int idx)
            {
                assert(idx <= _constBuffers.size());
                if (_constBuffers[idx].buffer != NULL)
                {
                    CALname name = getConstName(idx);
                    CALcontext ctx = _device->getContext();

                    CALresult result = calCtxSetMem(ctx, name, NULL);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to unbind constant memory\n");

                    // release mem handle
                    calCtxReleaseMem(_device->getContext(), _constBuffers[idx].mem);
                    _constBuffers[idx] = BufferItem();
                }
                return true;
            }

            bool Program::unbindGlobal()
            {
                if (_globalBuffer.buffer != NULL)
                {
                    CALname name = getGlobalName();
                    CALcontext ctx = _device->getContext();

                    CALresult result = calCtxSetMem(ctx, name, NULL);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to unbind constant memory\n");

                    // release mem handle
                    calCtxReleaseMem(_device->getContext(), _globalBuffer.mem);
                    _globalBuffer = BufferItem();
                }
                return false;
            }

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
                    _outputBuffers[idx].buffer->setInputEvent(e);
                }
                if (_globalBuffer.buffer)
                {
                    _globalBuffer.buffer->setOutputEvent(e);   
                }
                       
            }

            void Program::waitEvents()
            {
                // Comment the const buffer and global buffer, will not be nessecary now.
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
                //if (_globalBuffer.buffer)
                //{
                //    _globalBuffer.buffer->waitInputEvent(e);
                //}
            }

            Event* Program::run(const CALdomain &domain)
            {
                CALevent execEvent;
                CALcontext ctx = _device->getContext();

                syncConstBuffers();

                waitEvents();

                CALresult result = calCtxRunProgram(&execEvent, ctx, _func, &domain);
                CHECK_CAL_RESULT_ERROR2(result, "Failed to execute program!\n");

                result = calCtxIsEventDone(ctx, execEvent);
                if (result == CAL_RESULT_ERROR)
                {
                    fprintf(stderr, "Event error!\n");
                    return NULL;
                }

                Event* e = 
                    Runtime::getInstance()->getProgramManager()->getEvent();

                e->set(execEvent, ctx);

                setEvents(e);

                return e;
            }
        }
    }
}
