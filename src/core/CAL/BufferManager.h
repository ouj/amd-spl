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
#include <vector>

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Device;
            class Buffer;
            class ConstBuffer;
            class BufferManager
            {
                friend class Runtime;
            public:
                void destroyBuffer(Buffer* buffer);
                Buffer* createLocalBuffer(Device* device, CALformat format, unsigned int width, unsigned int height = 0);
                Buffer* createGlobalBuffer(Device* device, CALformat format, unsigned int width, unsigned int height = 0);
                Buffer* createRemoteBuffer(CALformat format, unsigned int width, unsigned int height = 0);

                ConstBuffer*    getConstBuffer(unsigned int size);
                void            releaseConstBuffer(ConstBuffer constBuf);
            protected:
                BufferManager();
                ~BufferManager();
                bool initialize();
            private:
                std::vector<ConstBuffer*> _usedConstBuf;
                std::vector<ConstBuffer*> _freeConstBuf;
            };
        }
    }
}

#endif  //_BUFFERMANAGER_H
