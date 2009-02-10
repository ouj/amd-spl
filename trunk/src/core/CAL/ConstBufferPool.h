//
//
//
//  @ Project : AMD-SPL
//  @ File Name : ConstBufferPool.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_CONSTBUFFERPOOL_H)
#define _CONSTBUFFERPOOL_H

#include "ConstBuffer.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class ConstBufferPool
            {
                friend class Runtime;
            public:
                ConstBuffer* getConstBuffer(int size);
                void releaseConstBuffer(ConstBuffer* constBuf);
            protected:
                ~ConstBufferPool();
                ConstBufferPool();
            private:
                std::vector<ConstBuffer*> _usedConstBuf;
                std::vector<ConstBuffer*> _freeConstBuf;
            };
        }
    }
}

#endif  //_CONSTBUFFERPOOL_H
