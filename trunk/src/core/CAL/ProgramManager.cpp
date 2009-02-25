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
                for(unsigned int i = 0; i < _eventPool.size(); ++i)
                {
                    SAFE_DELETE(_eventPool[i]);
                }
            }
            
            bool ProgramManager::initialize()
            {
                return true;
            }
            
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
