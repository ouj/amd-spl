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
#include <vector>

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
                Program*    loadProgram(const ProgInfo &progInfo, Device* device = NULL);
                void        unloadProgram(Program* program);
                Event*      getEvent();
            protected:
                            ProgramManager();
                            ~ProgramManager();
                bool        initialize();
            private:
                vector<Event*>  _eventPool;
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
            Program* ProgramManager::loadProgram(const ProgInfo &progInfo, Device* device)
            {
                if (device == NULL)
                {
                    // use the default device;
                    device = 
                        Runtime::getInstance()->getDeviceManager()->getDefaultDevice();
                }

                Program *prog = new Program(device);
                if (!prog->initialize(progInfo))
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
