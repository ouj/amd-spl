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
            //! \return	Buffer* The pointer to a LocalBuffer object if it is  
            //!                 successfully allocated. NULL if there is an error 
            //!                 during local buffer creation.
            //!
            //! \brief	Create a LocalBuffer object with specific CAL format and 
            //!         dimension
            //!
            //////////////////////////////////////////////////////////////////////////
            Buffer* BufferManager::createLocalBuffer(Device* device, CALformat format, 
                unsigned int width, unsigned int height)
            {
                LocalBuffer *localBuf = new LocalBuffer(device, format, width, height);
                if (!localBuf->initialize())
                {
                    SAFE_DELETE(localBuf);
                    return NULL;
                }
                return localBuf;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	device  The device where the GlobalBuffer will be located.
            //! \param	format  The CAL format of the GlobalBuffer.
            //! \param	width   The width of the 1D/2D buffer.
            //! \param	height  The height of the 2D buffer. It should be set to zero
            //!                 for 1D buffer.
            //! \return	Buffer* The pointer to a GlobalBuffer object if it is  
            //!                 successfully allocated. NULL if there is an error 
            //!                 during global buffer creation.
            //!
            //! \brief	Create a GlobalBuffer object with specific CAL format and 
            //!         dimension
            //!
            //////////////////////////////////////////////////////////////////////////
            Buffer* BufferManager::createGlobalBuffer(Device* device, CALformat format, 
                unsigned int width, unsigned int height)
            {
                GlobalBuffer *globalBuf = new GlobalBuffer(device, format, width, height);
                if (!globalBuf->initialize())
                {
                    SAFE_DELETE(globalBuf);
                    return NULL;
                }
                return globalBuf;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	format  The CAL format of the GlobalBuffer.
            //! \param	width   The width of the 1D/2D buffer.
            //! \param	height  The height of the 2D buffer. It should be set to zero
            //!                 for 1D buffer.
            //! \return	Buffer* The pointer to a RemoteBuffer object if it is 
            //!                 successfully allocated. NULL if there is an error 
            //!                 during remote buffer creation.
            //!
            //! \brief	Create a RemoteBuffer object with specific CAL format and 
            //!         dimension
            //!
            //////////////////////////////////////////////////////////////////////////
            Buffer* BufferManager::createRemoteBuffer(CALformat format, unsigned int width, 
                unsigned int height)
            {
                RemoteBuffer *remoteBuf = new RemoteBuffer(format, width, height);
                if (!remoteBuf->initialize())
                {
                    SAFE_DELETE(remoteBuf);
                    return NULL;
                }
                return remoteBuf;
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
                if (_constBufferPool.size())
                {
                    constBuf = _constBufferPool.back();
                    _constBufferPool.pop_back();
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
                    _constBufferPool.push_back(constBuf);
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
                    _constBufferPool.push_back(constBuf);
                }
            }
        }
    }
}
