//
//
//
//  @ Project : AMD-SPL
//  @ File Name : ProgramManager.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_PROGRAMMANAGER_H)
#define _PROGRAMMANAGER_H

#include "Program.h"
#include "CommonDefs.h"
#include <map>

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class ProgramManager
            {
                friend class Runtime;
            public:
                template<typename ProgInfo>
                Program* loadProgram(Device* device);
                void unloadProgram(Program* program);
            protected:
                std::map<string, Program*> _programCache;
                ProgramManager();
                ~ProgramManager();
                bool initialize();
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
            template<typename ProgInfo>
            Program* ProgramManager::loadProgram(Device* device)
            {
                Program *prog = new Program(device);

                if (!prog->initialize<ProgInfo>())
                {
                    SAFE_DELETE(prog);
                    return NULL;
                }
                return prog;
            }
        }
    }
}
#endif  //_PROGRAMMANAGER_H
