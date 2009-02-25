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
                friend class BufferManager;
            public:
                ~ConstBuffer();
                template<unsigned int I, typename T>
                bool setConstant(T* pVal);
                bool sync();
            protected:
                ConstBuffer();
                bool resize(unsigned int size);
            private:
                enum
                {
                    MAX_CONST_NUM = 64
                };
                std::vector<float4> _buffer;
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
            template<unsigned int I, typename T>
            bool ConstBuffer::setConstant(T* pVal)
            {
                if (sizeof(T) > sizeof(float4))
                {
                    return false;
                }
                memcpy(&_buffer[I], data, sizeof(T));
            }
        }
    }
}

#endif  //_CONSTBUFFER_H
