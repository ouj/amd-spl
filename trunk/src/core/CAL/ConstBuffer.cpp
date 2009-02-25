//
//
//
//  @ Project : AMD-SPL
//  @ File Name : ConstBuffer.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#include "ConstBuffer.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            ConstBuffer::ConstBuffer() : 
                RemoteBuffer(CAL_FORMAT_FLOAT_4, MAX_CONST_NUM, 0), _buffer(MAX_CONST_NUM)
            {
            }

            bool ConstBuffer::resize(unsigned int size)
            {
                if (size > MAX_CONST_NUM)
                {
                    fprintf(stderr, "Constant buffer size cannot exceed %d\n", MAX_CONST_NUM);
                    return false;
                }

                _buffer.resize(size);
                return true;
            }

            ConstBuffer::~ConstBuffer()
            {

            }

            bool ConstBuffer::sync()
            {
                CALuint pitch;
                void* data = getPointerCPU(pitch);
                if(!data)
                {
                    return false;
                }
                memcpy(data, &_buffer[0], _buffer.size() * sizeof(float4));
                releasePointerCPU();
                return true;
            }
        }
    }
}
