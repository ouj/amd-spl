//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		BufferManager.cpp
//!	\date 		27:2:2009   22:17
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of BufferManager class.
//!
//////////////////////////////////////////////////////////////////////////

#include "RuntimeDefs.h"
#include "CommonDefs.h"
namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Constructor
            //!
            //! \brief	Construct the BufferManager. It will not be available until
            //!         BufferManager::initialize() is called.
            //!
            //////////////////////////////////////////////////////////////////////////
            BufferManager::BufferManager()
            {

            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy the BufferManager.
            //!
            //////////////////////////////////////////////////////////////////////////
            BufferManager::~BufferManager()
            {

            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool True if the BufferManager is successfully initialized.
            //!              False if there is an error during initialization.
            //!
            //! \brief	Initialize the BufferManager. (Note: Currently this method
            //!         does nothing).
            //!
            //////////////////////////////////////////////////////////////////////////
            bool BufferManager::initialize()
            {
                return true;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	buffer The pointer to the buffer to be destroyed.
            //!
            //! \brief	Destroy a buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            void BufferManager::destroyBuffer(Buffer* buffer)
            {
                SAFE_DELETE(buffer);
            }
            
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	device  The device where the LocalBuffer will be located.
            //! \param	format  The CAL format of the LocalBuffer.
            //! \param	width   The width of the 1D/2D buffer.
            //! \param	height  The height of the 2D buffer. It should be set to zero
            //!                 for 1D buffer.
            //! \param  flag    The buffer initialization flag.
            //! \return	Buffer* The pointer to a LocalBuffer object if it is  
            //!                 successfully allocated. NULL if there is an error 
            //!                 during local buffer creation.
            //!
            //! \brief	Create a LocalBuffer object with specific CAL format and 
            //!         dimension
            //!
            //////////////////////////////////////////////////////////////////////////
            Buffer* BufferManager::createLocalBuffer(Device* device, CALformat format, 
                unsigned int width, unsigned int height, unsigned int flag)
            {
                LocalBuffer *localBuf = 
                    new LocalBuffer(device, format, width, height, flag);
                if (!localBuf->initialize())
                {
                    SAFE_DELETE(localBuf);
                    return NULL;
                }
                return localBuf;
            }


            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	format  The CAL format of the GlobalBuffer.
            //! \param	width   The width of the 1D/2D buffer.
            //! \param	height  The height of the 2D buffer. It should be set to zero
            //!                 for 1D buffer.
            //! \param  flag    The buffer initialization flag.
            //! \return	Buffer* The pointer to a RemoteBuffer object if it is 
            //!                 successfully allocated. NULL if there is an error 
            //!                 during remote buffer creation.
            //!
            //! \brief	Create a RemoteBuffer object with specific CAL format and 
            //!         dimension
            //!
            //////////////////////////////////////////////////////////////////////////
            Buffer* BufferManager::createRemoteBuffer(CALformat format, unsigned int width, 
                unsigned int height, unsigned int flag)
            {
                RemoteBuffer *remoteBuf = new RemoteBuffer(format, width, height, flag);
                if (!remoteBuf->initialize())
                {
                    SAFE_DELETE(remoteBuf);
                    return NULL;
                }
                return remoteBuf;
            }

			//////////////////////////////////////////////////////////////////////////
            //!
            //! \param	device  The device where the PinnedBuffer will be located.
            //! \param	format  The CAL format of the PinnedBuffer.
            //! \param	width   The width of the 1D/2D buffer.
            //! \param	height  The height of the 2D buffer. It should be set to zero
            //!                 for 1D buffer.
            //! \param  flag    The buffer initialization flag.
            //! \return	Buffer* The pointer to a PinnedBuffer object if it is  
            //!                 successfully allocated. NULL if there is an error 
            //!                 during local buffer creation.
            //!
            //! \brief	Create a PinnedBuffer object with specific CAL format and 
            //!         dimension
            //!
            //////////////////////////////////////////////////////////////////////////
            Buffer* BufferManager::createPinnedBuffer(Device* device, CALformat format, 
                unsigned int width, unsigned int height, void *userMem, unsigned int flag)
            {
                PinnedBuffer *pinnedBuf = 
                    new PinnedBuffer(device, format, width, height, userMem);
                if (!pinnedBuf->initialize())
                {
                    SAFE_DELETE(pinnedBuf);
                    return NULL;
                }
                return pinnedBuf;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	size            The size of the constant buffer.
            //! \return	ConstBuffer*    The pointer to a ConstBuffer object. NULL if 
            //!                         failed to retrieve the ConstBuffer from the
            //!                         pool.
            //!
            //! \brief	Get a ConstBuffer object from the constant buffer pool.
            //!
            //////////////////////////////////////////////////////////////////////////
            ConstBuffer* BufferManager::getConstBuffer(unsigned int size)
            {
                ConstBuffer *constBuf;
                CONST_BUF_SIZE cbsize;
                if (size > 4096)
                    return NULL;
                else if (size > 1024)
                    cbsize = CB4096;
                else if (size > 256)
                    cbsize = CB1024;
                else if (size > 64)
                    cbsize = CB256;
                else
                    cbsize = CB64;

                if (_constBufferPools[cbsize].size())
                {
                    constBuf = _constBufferPools[cbsize].back();
                    _constBufferPools[cbsize].pop_back();
                }
                else
                {
                    constBuf = new ConstBuffer();
                    if(!constBuf->initialize())
                    {
                        SAFE_DELETE(constBuf);
                        return NULL;
                    }
                }
                if(!constBuf->resize(size))
                {
                    // you break the rule, you get nothing;
                    _constBufferPools[cbsize].push_back(constBuf);
                    return NULL;
                }
                return constBuf;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	constBuf    The pointer to the ConstBuffer object, which is 
            //!                     going to be release back to the pool.
            //!
            //! \brief	Release a ConstBuffer object back to the pool.
            //!
            //////////////////////////////////////////////////////////////////////////
            void BufferManager::releaseConstBuffer(ConstBuffer *constBuf)
            {
                if (constBuf)
                {
                    CONST_BUF_SIZE cbsize;
                    unsigned int size = constBuf->getWidth();
                    if (size > 4096)
                    {
                        fprintf(stderr, "Error Constant buffer size.");
                        assert(false);
                        return;
                    }
                    else if (size > 1024)
                        cbsize = CB4096;
                    else if (size > 256)
                        cbsize = CB1024;
                    else if (size > 64)
                        cbsize = CB256;
                    else
                        cbsize = CB64;
                    _constBufferPools[cbsize].push_back(constBuf);
                }
            }
        }
    }
}
