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
                friend class BufferManager;
            public:
                virtual ~Buffer();
                virtual bool readData(void *ptr, unsigned long size, void *defaultVal = 0);
                virtual bool writeData(void *ptr, unsigned long size);
                CALresource getResHandle();
                CALformat getFormat();
                unsigned int getPitch();
                unsigned int getWidth();
                unsigned int getHeight();
            protected:
                CALformat _dataFormat;
                CALresource _res;
                unsigned int _width;
                unsigned int _height;
                CALuint      _pitch;
                Buffer(CALformat format, unsigned int width, unsigned int height = 0);
                virtual bool initialize();
                void* getPointerCPU(CALuint &pitch);
                void releasePointerCPU();
            };
        }
    }
}

#endif  //_BUFFER_H
