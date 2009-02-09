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
            Program::Program()
            {
            
            }
            
            Program::~Program()
            {
            
            }
            
            bool Program::load(Device* device)
            {
                return true;
            }
            
            bool Program::unload()
            {
                return true;
            }
            
            void Program::bindInput(Buffer* buffer, unsigned int idx)
            {
            
            }
            
            void Program::bindOutput(Buffer* buffer, unsigned int idx)
            {
            
            }
            
            void Program::bindConstant(ConstBuffer* buffer, unsigned int idx)
            {
            
            }
            
            void Program::bindScatter(ScatterBuffer* buffer, unsigned int idx)
            {
            
            }
            
            bool Program::build(Device* device)
            {
                return true;
            }

            Event Program::run(CALdomain domain)
            {
                return Event();
            }
            
        }
    }
}
