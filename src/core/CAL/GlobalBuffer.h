//
//
//
//  @ Project : AMD-SPL
//  @ File Name : GlobalBuffer.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_GLOBALBUFFER_H)
#define _GLOBALBUFFER_H

#include "LocalBuffer.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class GlobalBuffer : public LocalBuffer
            {
                friend class BufferManager;
            protected:
                GlobalBuffer(Device* device, CALformat format, 
                    unsigned int width, unsigned int height = 0);
                virtual bool initialize();
            };
        }
    }
}

#endif  //_GLOBALBUFFER_H
