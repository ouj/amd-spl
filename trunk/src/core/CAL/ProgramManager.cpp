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
            void ProgramManager::unloadProgram(Program* program)
            {
                SAFE_DELETE(program);
            }
            
            ProgramManager::ProgramManager()
            {
            
            }
            
            ProgramManager::~ProgramManager()
            {
            
            }
            
            bool ProgramManager::initialize()
            {
                return true;
            }
        }
    }
}
