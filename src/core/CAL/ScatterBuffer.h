//
//
//
//  @ Project : AMD-SPL
//  @ File Name : ScatterBuffer.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_SCATTERBUFFER_H)
#define _SCATTERBUFFER_H

#include "LocalBuffer.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class ScatterBuffer : public LocalBuffer
            {
            protected:
                bool initialize();
            };
        }
    }
}

#endif  //_SCATTERBUFFER_H
