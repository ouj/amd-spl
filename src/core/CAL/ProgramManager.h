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
                Program* loadProgram();
                void unloadPorgram(Program* program);
            protected:
                std::map<string, Program*> _programCache;
                ProgramManager();
                ~ProgramManager();
                bool initialize();
            };
        }
    }
}

#endif  //_PROGRAMMANAGER_H
