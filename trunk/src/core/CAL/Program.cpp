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
                assert(idx <= _inputMems.size());
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

                _inputMems[idx] = mem;

                return true;
            }
            
            bool Program::bindOutput(Buffer* buffer, unsigned int idx)
            {
                assert(idx <= _outputMems.size());
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

                _outputNames[idx] = mem;

                return true;
            }
            
            bool Program::bindConstant(ConstBuffer* buffer, unsigned int idx)
            {
                assert(idx <= _constMems.size());
                return false;
            }
            
            bool Program::bindGlobal(GlobalBuffer* buffer)
            {
                return false;
            }

            bool Program::unbindInput(unsigned int idx)
            {
                assert(idx <= _inputMems.size());
                if (_inputMems[idx] != NULL)
                {
                    CALname name = getInputName(idx);
                    CALcontext ctx = _device->getContext();

                    CALresult result = calCtxSetMem(ctx, name, NULL);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to unbind input memory\n");

                    // release mem handle
                    calCtxReleaseMem(_device->getContext(), _inputMems[idx]);
                    _inputMems[idx] = NULL;
                }

                return true;
            }

            bool Program::unbindOutput(unsigned int idx)
            {
                assert(idx <= _outputMems.size());
                if (_outputMems[idx] != NULL)
                {
                    CALname name = getInputName(idx);
                    CALcontext ctx = _device->getContext();

                    CALresult result = calCtxSetMem(ctx, name, NULL);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to unbind input memory\n");

                    // release mem handle
                    calCtxReleaseMem(_device->getContext(), _outputMems[idx]);
                    _outputMems[idx] = NULL;
                }
                return true;
            }

            bool Program::unbindConstant(unsigned int idx)
            {
                return false;
            }

            bool Program::unbindGlobal()
            {
                return false;
            }

            bool Program::unbindAll()
            {
                bool result = true;
                result = unbindGlobal() ? result : false;
                for (unsigned int idx = 0; idx < _constMems.size(); idx++)
                {
                    result = unbindConstant(idx) ? result : false;
                }
                for (unsigned int idx = 0; idx < _inputMems.size(); idx++)
                {
                    result = unbindInput(idx) ? result : false;
                }
                for (unsigned int idx = 0; idx < _outputMems.size(); idx++)
                {
                    result = unbindOutput(idx) ? result : false;
                }
                return result;
            }

            Event Program::run(CALdomain domain)
            {
                return Event(NULL);
            }
        }
    }
}
