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
                virtual void readData(void *ptr, unsigned int size);
                virtual void writeData(void *ptr, unsigned int size, void *defaultVal = 0);
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
