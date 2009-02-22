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
            class Device;
            class LocalBuffer : public Buffer
            {
                friend class BufferManager;
            public:
                ~LocalBuffer();
                //virtual void readData(void* ptr, unsigned int size, void* defaultVal = 0);
                //virtual void writeData(void* ptr, unsigned int size);
            protected:
                LocalBuffer(Device* device, CALformat format, 
                    unsigned int width, unsigned int height = 0);
                virtual bool initialize();
                Device* _device;
            };
        }
    }
}

#endif  //_LOCALBUFFER_H