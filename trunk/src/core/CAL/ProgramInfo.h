//
//
//
//  @ Project : AMD-SPL
//  @ File Name : ProgramInfo.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_PROGRAMINFO_H)
#define _PROGRAMINFO_H


#define DCL_PROGRAM_SOURCE(ProgInfo) const char* (ProgInfo::source)
#define DCL_PROGRAM_ID(ProgInfo) const char* (ProgInfo::programID)

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            template <int outputsT, int inputsT = 0, int constantsT = 0, int globalsT = 0> 
            class ProgramInfo
            {
            public:
                enum para
                {
                    outputs = outputsT,
                    inputs = inputsT,
                    constants = constantsT,
                    globals = globalsT
                };
                static const char* source;
                static const char* programID;
            };
        }
    }
}

#endif  //_PROGRAMINFO_H
