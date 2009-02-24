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
                virtual Event   run(const CALdomain &domain);
                bool            bindInput(Buffer* buffer, unsigned int idx);
                bool            bindOutput(Buffer* buffer, unsigned int idx);
                bool            bindConstant(ConstBuffer* buffer, unsigned int idx);
                bool            bindGlobal(GlobalBuffer* buffer);

                bool            unbindInput(unsigned int idx);
                bool            unbindOutput(unsigned int idx);
                bool            unbindConstant(unsigned int idx);
                bool            unbindGlobal();
                bool            unbindAll();

                inline CALname  getOutputName(unsigned short i) const;
                inline CALname  getInputName(unsigned short i) const;
                inline CALname  getConstName(unsigned short i) const;
                inline CALname  getGlobalName() const;
            protected:
                vector<CALname>         _inputNames;
                vector<CALname>         _outputNames;
                vector<CALname>         _constNames;
                CALname                 _globalName;

                vector<CALmem>          _inputMems;
                vector<CALmem>          _outputMems;
                vector<CALmem>          _constMems;
                CALmem                  _globalMem;

                CALfunc                 _func;
                CALmodule               _module;
                Device*                 _device;
            };
        }
    }
}

#include "ProgramDefs.h"

#endif  //_PROGRAM_H
