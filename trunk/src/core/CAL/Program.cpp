//
//
//
//  @ Project : AMD-SPL
//  @ File Name : Program.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


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
                CALcontext ctx = _device->getContext();

                // Destroy the module
                if(_module)
                {
                    calModuleUnload(ctx, _module);
                }
            }
            
            CALname Program::getOutputName(unsigned short i) const
            {
                return _outputNames[i];
            }

            CALname Program::getInputName(unsigned short i) const
            {
                return _inputNames[i];
            }

            CALname Program::getConstName(unsigned short i) const
            {
                return _constNames[i];
            }

            CALname Program::getGlobalName() const
            {
                return _globalName;
            }

            bool Program::bindInput(Buffer* buffer, unsigned int idx)
            {
                return false;
            }
            
            bool Program::bindOutput(Buffer* buffer, unsigned int idx)
            {
                return false;
            }
            
            bool Program::bindConstant(ConstBuffer* buffer, unsigned int idx)
            {
                return false;
            }
            
            bool Program::bindGlobal(GlobalBuffer* buffer)
            {
                return false;
            }

            void Program::unbindAll()
            {

            }

            Event Program::run(CALdomain domain)
            {
                return Event(NULL);
            }
        }
    }
}
