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
#include <stdio.h>
#include "calcl.h"
#include "CommonDefs.h"

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
                Program(Device *device);
                ~Program();
                template<typename ProgInfo>
                bool            initialize();
                virtual Event   run(CALdomain domain);
                bool            bindInput(Buffer* buffer, unsigned int idx = 0);
                bool            bindOutput(Buffer* buffer, unsigned int idx = 0);
                bool            bindConstant(ConstBuffer* buffer, unsigned int idx = 0);
                bool            bindGlobal(GlobalBuffer* buffer);
                void            unbindAll();

                CALname         getOutputName(unsigned short i) const;
                CALname         getInputName(unsigned short i) const;
                CALname         getConstName(unsigned short i) const;
                CALname         getGlobalName() const;
            protected:
                vector<CALname>         _inputNames;
                vector<CALname>         _outputNames;
                vector<CALname>         _constNames;
                CALname                 _globalName;

                vector<Buffer*>         _inputBuffers;
                vector<Buffer*>         _outputBuffers;
                vector<ConstBuffer*>    _constBuffers;
                GlobalBuffer*           _globalBuffer;

                CALfunc                 _func;
                CALmodule               _module;
                Device*                 _device;
            };
        }
    }
}

#include "ProgramDefs.h"

#endif  //_PROGRAM_H
