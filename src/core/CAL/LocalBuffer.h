//
//
//
//  @ Project : AMD-SPL
//  @ File Name : LocalBuffer.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_LOCALBUFFER_H)
#define _LOCALBUFFER_H

#include "Buffer.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class LocalBuffer : public Buffer
            {
            public:
                void readData(void* ptr, unsigned int size);
                void writeData(void* ptr, unsigned int size);
            protected:
                LocalBuffer(CALformat format, unsigned int width, unsigned int height = 0);
                bool initialize();
            private:
                unsigned short _deviceId;
            };
        }
    }
}

#endif  //_LOCALBUFFER_H
