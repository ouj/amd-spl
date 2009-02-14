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


namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            template <int inputs, int outputs, int constants, int scatters> 
            class ProgramInfo
            {
            public:
                const char* source;
                const char* programID;
            };
        }
    }
}

#endif  //_PROGRAMINFO_H
