//
//
//
//  @ Project : AMD-SPL
//  @ File Name : RemoteBuffer.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_REMOTEBUFFER_H)
#define _REMOTEBUFFER_H

#include "Buffer.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class RemoteBuffer : public Buffer
            {
                friend class BufferManager;
            protected:
                RemoteBuffer(CALformat format, unsigned int width, unsigned int height = 0);
                virtual bool initialize();
                bool _cachable;
            };
        }
    }
}

#endif  //_REMOTEBUFFER_H