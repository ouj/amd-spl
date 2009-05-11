#ifndef AMDSPL_BUFFERMANAGER_H_
#define AMDSPL_BUFFERMANAGER_H_
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
#include "SplDefs.h"
#include <vector>

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            enum CONST_BUF_SIZE
            {
                CB64,
                CB256,
                CB1024,
                CB4096,
                CONST_BUF_SIZE_NUM
            };
            class Device;
            class Buffer;
            class ConstBuffer;
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	BufferManager class contains factory methods for LocalBuffer,
            //!         RemoteBuffer and GlobalBuffer. It also contains a ConstBuffer
            //!         pool, which will avoid frequently allocate and deallocate
            //!         ConstBuffer. Created when the runtime is initialized and 
            //!         deleted when the runtime is destroyed.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class SPL_EXPORT BufferManager
            {
                friend class Runtime;
            public:
                void            destroyBuffer(Buffer* buffer);
                bool            copy(Buffer* src, Buffer* dst, Device *device = 0);
                Buffer*         createLocalBuffer(Device* device, CALformat format, 
                                                  unsigned int width, unsigned int height = 0, unsigned int flag = 0);
                Buffer*         createRemoteBuffer(CALformat format, unsigned int width, 
                                                    unsigned int height = 0, unsigned int flag = 0);
				Buffer*         createPinnedBuffer(Device* device, CALformat format, 
													unsigned int width, unsigned int height, void *userMem, unsigned int flag = 0);
                ConstBuffer*    getConstBuffer(unsigned int size);
                void            releaseConstBuffer(ConstBuffer *constBuf);
            protected:
                BufferManager();
                ~BufferManager();
                bool initialize();
            private:
                //! \brief	The constant buffer pool.
                std::vector<ConstBuffer*>   _constBufferPools[CONST_BUF_SIZE_NUM];
            };
        }
    }
}

#endif  // AMDSPL_BUFFERMANAGER_H_
