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

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief Define Program information type for copy kernel. Internal use
            //!         only.
            //!
            //////////////////////////////////////////////////////////////////////////
            typedef ProgramInfo<1, 1, 0, false>  CopyKernelProgram;
            //! \brief	Copy kernel source string. Static object, internal use only.
            static const char* _sz_copy_kernel_source_ = IL_KERNEL(
                il_ps_2_0
                dcl_input_position_interp(linear_noperspective) v0.xy__
                dcl_output_generic o0
                dcl_resource_id(0)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)
                sample_resource(0)_sampler(0) o0, v0.xy00
                endmain
                end
                );
            //! \brief	Copy kernel ProgramInfo object. Static object, internal use only.
            static CopyKernelProgram copyKernel = 
                CopyKernelProgram("Copy Kernel", _sz_copy_kernel_source_);

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	src The source buffer.
            //! \param	dst The destination buffer.
            //! \param	device The device copy kernel used.
            //! \return	bool True if the copy is succeeded. False if the copy is 
            //!              failed
            //!
            //! \brief	Copy the content of source buffer to the dst buffer. The 
            //!         buffers' format are required to be the same and the src 
            //!         size is not smaller than the destination buffer. The copy
            //!         domain is set to be the size of destination buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool BufferManager::copy(Buffer* src, Buffer* dst, Device *device)
            {
                if(src->getFormat() != dst->getFormat())
                {
                    LOG_ERROR("Source buffer format is different from the destination buffer format.\n");
                    return false;
                }
                if (dst->getWidth() > src->getWidth() || dst->getHeight() > src->getHeight())
                {
                    LOG_ERROR("Source buffer is smaller than the destination buffer");
                    return false;
                }
                ProgramManager* progMgr = Runtime::getInstance()->getProgramManager();
                assert(progMgr);

                if (!device)
                {
                    device = Runtime::getInstance()->getDeviceManager()->getDefaultDevice();
                }

                Program *program = progMgr->loadProgram(copyKernel, device);
                assert(program);

                if(!program->bindInput(src, 0))
                {
                    assert(false);
                    return false;
                };
                if(!program->bindOutput(dst, 0))
                {
                    assert(false);
                    return false;
                };

                CALdomain domain = {0, 0, dst->getWidth(), dst->getHeight() ? dst->getHeight() : 1};
                Event *e = program->run(domain);
                assert(e);
                if (!e)
                {
                    LOG_ERROR("Failed to execute copy kernel.\n");
                    return false;
                }

                progMgr->unloadProgram(program);
                return true;
            }
        }
    }
}
