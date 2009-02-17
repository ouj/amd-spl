//
//
//
//  @ Project : AMD-SPL
//  @ File Name : Program.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_PROGRAM_H)
#define _PROGRAM_H

#include "Event.h"
#include "Device.h"
#include <vector>

using namespace std;

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Buffer;
            class ConstBuffer;
            class GlobalBuffer;

            class Program
            {
            public:
                Program();
                ~Program();
                bool load(Device* device);
                bool unload();
                virtual Event run(CALdomain domain);
                void bindInput(Buffer* buffer, unsigned int idx = 0);
                void bindOutput(Buffer* buffer, unsigned int idx = 0);
                void bindConstant(ConstBuffer* buffer, unsigned int idx = 0);
                void bindGlobal(GlobalBuffer* buffer, unsigned int idx = 0);
            protected:
                CALobject _object;
                vector<CALimage> _image;
                vector<CALname> _inputNames;
                vector<CALname> _outputNames;
                vector<CALname> _constNames;
                vector<CALname> _globalNames;
                CALfunc _func;
                CALmodule _module;
                Device* _device;
                bool build(Device* device);
            };
        }
    }
}

#endif  //_PROGRAM_H
