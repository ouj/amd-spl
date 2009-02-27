#if !defined(_BUFFERMANAGER_H)
#define _BUFFERMANAGER_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		BufferManager.h
//!	\date 		27:2:2009   22:17
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of BufferManager class.
//!
//////////////////////////////////////////////////////////////////////////
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
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	The BufferManager contains factory methods for LocalBuffer,
            //!         RemoteBuffer and GlobalBuffer. It also contains a ConstBuffer
            //!         pool, which will avoid frequently allocate and deallocate
            //!         ConstBuffer. Created when the runtime is initialized and 
            //!         deleted when the runtime is destroyed.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class BufferManager
            {
                friend class Runtime;
            public:
                void destroyBuffer(Buffer* buffer);
                Buffer* createLocalBuffer(Device* device, CALformat format, unsigned int width, unsigned int height = 0);
                Buffer* createGlobalBuffer(Device* device, CALformat format, unsigned int width, unsigned int height = 0);
                Buffer* createRemoteBuffer(CALformat format, unsigned int width, unsigned int height = 0);

                ConstBuffer*    getConstBuffer(unsigned int size);
                void            releaseConstBuffer(ConstBuffer *constBuf);
            protected:
                BufferManager();
                ~BufferManager();
                bool initialize();
            private:
                //! \brief	The constant buffer pool.
                std::vector<ConstBuffer*> _constBufferPool;
            };
        }
    }
}

#endif  //_BUFFERMANAGER_H
