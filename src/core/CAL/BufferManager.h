//
//
//
//  @ Project : AMD-SPL
//  @ File Name : BufferManager.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_BUFFERMANAGER_H)
#define _BUFFERMANAGER_H
#include "cal.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Buffer;
            class BufferManager
            {
                friend class Runtime;
            public:
                void destroyBuffer(Buffer* buffer);
                Buffer* createLocalBuffer(CALformat format, unsigned int width, unsigned int height = 0);
                Buffer* createRemoatBuffer(CALformat format, unsigned int width, unsigned int height = 0);
            protected:
                BufferManager();
                ~BufferManager();
                bool initialize();
            };
        }
    }
}

#endif  //_BUFFERMANAGER_H
