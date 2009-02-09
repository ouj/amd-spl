//
//
//
//  @ Project : AMD-SPL
//  @ File Name : ConstBuffer.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_CONSTBUFFER_H)
#define _CONSTBUFFER_H

#include "RemoteBuffer.h"
#include <vector>
#include "VectorDataType.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class ConstBuffer : public RemoteBuffer
            {
            public:
                void setConstant();
                void sync();
            protected:
                std::vector<float4> _buffer;
            };
        }
    }
}

#endif  //_CONSTBUFFER_H
