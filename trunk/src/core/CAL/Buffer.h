//
//
//
//  @ Project : AMD-SPL
//  @ File Name : Buffer.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_BUFFER_H)
#define _BUFFER_H
#include "cal.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Buffer
            {
            public:
                void readData(void *ptr, unsigned int size);
                void writeData(void *ptr, unsigned int size);
                void getResHandle();
                void getFormat();
                void getPitch();
                unsigned int getWidth();
                unsigned int getHeight();
                void getBufferType();
            protected:
                CALformat _dataFormat;
                CALresource _res;
                CALmem _mem;
                unsigned int _width;
                unsigned int _height;
                Buffer(CALformat format, unsigned int width, unsigned int height = 0);
                void initializa();
                void getCPUPointer();
                void releaseCPUPointer();
            };
        }
    }
}

#endif  //_BUFFER_H
