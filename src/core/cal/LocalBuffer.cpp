//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		LocalBuffer.cpp
//!	\date 		1:3:2009   14:05
//!	\author		Jiawei Ou, Shawn Zhou
//!	
//!	\brief		Contains definition of LocalBuffer object.
//!
//////////////////////////////////////////////////////////////////////////
#include "RuntimeDefs.h"
#include "LocalBuffer.h"
#include "Device.h"
#include <stdio.h>

#define DMA_TRANSFER

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	device  The pointer to the Device object this local buffer 
            //!                 associated to.
            //! \param	format  The CAL format of the local buffer.
            //! \param	width   The width of 1D/2D local buffer.
            //! \param	height  The height of 2D local buffer. For 1D local buffer,
            //!                 this value should be set to zero.
            //! \return	
            //!
            //! \brief	Construct the LocalBuffer object.The object will not be 
            //!         available until LocalBuffer::initialize() is called.
            //!
            //////////////////////////////////////////////////////////////////////////
            LocalBuffer::LocalBuffer(Device *device, CALformat format, unsigned int width, 
                unsigned int height, unsigned int flag)
                : Buffer(format, width, height, flag), _device(device)
            {
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy the LocalBuffer object.
            //!
            //////////////////////////////////////////////////////////////////////////
            LocalBuffer::~LocalBuffer()
            {
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool True if the local buffer is initialized successful. 
            //!         False if there is an error during initialization.
            //!
            //! \brief	Initialize the LocalBuffer object.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool LocalBuffer::initialize()
            {
                if (!_device)
                    return false;

                CALdeviceinfo info = _device->getInfo();
                if (_height == 0 || _height == 1) // 1D
                {
                    if (_width > info.maxResource1DWidth)
                    {
                        return false;
                    }
                    CALresult result = calResAllocLocal1D(&_res, _device->getHandle(), 
                        _width, _dataFormat, _flag);
                    CHECK_CAL_RESULT_ERROR(result, "Failed create 1D buffer\n");
                }
                else // 2D
                {
                    if (_width > info.maxResource2DWidth || _height > info.maxResource2DHeight)
                    {
                        return false;
                    }
                    CALresult result = calResAllocLocal2D(&_res, _device->getHandle(), 
                        _width, _height, _dataFormat, _flag);
                    CHECK_CAL_RESULT_ERROR(result, "Failed create 2D buffer\n");
                }
                return true;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	ptr     The CPU address contains the data going to be 
            //!                 transfered to the buffer.
            //! \param	size    The size in bytes of the data  the pointer points to.
            //! \return	bool    True if data transfer is succeeded. False if there is 
            //!                 an error during data transfer.
            //!
            //! \brief	Asynchronized data transfer from CPU memory to the local buffer.
            //!         Sometimes the buffer is larger than the data that is going to 
            //!         be transfered. In this case, if defaulVal is set, the method 
            //!         will set the rest of buffer using the default value pointed by 
            //!         defaultVal.
            //!
            //! \attention  It is the developers' responsibility to make sure the  
            //!             format and size of the CPU memory that ptr points to are 
            //!             valid.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool LocalBuffer::readData(void *ptr, unsigned long size)
            {
                if (!ptr)
                    return false;

                waitInputEvent();

                BufferManager* bufMgr = Runtime::getInstance()->getBufferManager();
                assert(bufMgr);

                // Try to get cachable resource
                Buffer *hostBuf = 
                    bufMgr->createRemoteBuffer(_dataFormat, _width, _height, CAL_RESALLOC_CACHEABLE);
                if(!hostBuf)
                {
                    // failed..-_-, try again using uncachable memory.
                    LOG_COMMON_ERROR("Failed to create cachable host memory, try uncachable\n");
                    Buffer *hostBuf = 
                        bufMgr->createRemoteBuffer(_dataFormat, _width, _height);
                }
                if(!hostBuf)
                {

                    // failed again..x_x, fall back to normal routine.
                    LOG_COMMON_ERROR("Failed to create host memory, fall back to normal rountine\n");
                    return Buffer::readData(ptr, size);
                }
                if(!hostBuf->readData(ptr, size))
                    return false;

                CALresult result = CAL_RESULT_OK;
                CALcontext ctx = _device->getContext();
                assert(ctx);

                // Get the memory handle
                CALmem srcMem;
                CALmem dstMem;
                result = calCtxGetMem(&srcMem, ctx, hostBuf->getResHandle());
                CHECK_CAL_RESULT_ERROR(result, "Failed to get host memory handle \n");
                result = calCtxGetMem(&dstMem, ctx, _res);
                CHECK_CAL_RESULT_ERROR(result, "Failed to get local memory handle \n");

                Event* e = 
                    Runtime::getInstance()->getProgramManager()->getEvent();

                CALevent memcpyEvent;
                result = calMemCopy(&memcpyEvent, ctx, srcMem, dstMem, 0);
                CHECK_CAL_RESULT_ERROR(result, "Failed to do DMA transfer.\n");

                calCtxIsEventDone(ctx, memcpyEvent);
                e->set(memcpyEvent, ctx);
                setOutputEvent(e);

                calCtxReleaseMem(ctx, srcMem);
                CHECK_CAL_RESULT_ERROR(result, "Failed to release host memory handle \n");
                calCtxReleaseMem(ctx, dstMem);
                CHECK_CAL_RESULT_ERROR(result, "Failed to release local memory handle \n");
                bufMgr->destroyBuffer(hostBuf);
                return true;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	ptr     The CPU address where that data in buffer will be 
            //!                 transfered to.
            //! \param	size    The size in bytes of the space the pointer points to.
            //! \return	bool    True if data transfer is succeeded. False if there is 
            //!                 an error during data transfer.
            //!
            //! \brief	Synchronized data transfer from local buffer to CPU memory.
            //!         Instead of DMA, a copy kernel is used to have the peak 
            //!         performance.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool LocalBuffer::writeData(void *ptr, unsigned long size)
            {
                if (!ptr)
                    return false;

				waitOutputEvent();

                BufferManager* bufMgr = Runtime::getInstance()->getBufferManager();
                assert(bufMgr);

                // Try to get cachable resource
                Buffer *hostBuf = 
                    bufMgr->createRemoteBuffer(_dataFormat, _width, _height, CAL_RESALLOC_CACHEABLE);
                if(!hostBuf)
                {
                    // failed..-_-, try again using uncachable memory.
                    LOG_COMMON_ERROR("Failed to create cachable host memory, try uncachable\n");
                    Buffer *hostBuf = 
                        bufMgr->createRemoteBuffer(_dataFormat, _width, _height);
                }
                if(!hostBuf)
                {
                    // Fall back to normal routine.
                    LOG_COMMON_ERROR("Failed to create host memory, fall back to normal rountine\n");
                    return Buffer::writeData(ptr, size);
                }

                Event* e = bufMgr->copy(this, hostBuf, this->_device);

                if(!hostBuf->writeData(ptr, size))
                    return false;

                bufMgr->destroyBuffer(hostBuf);
                return true;
            }


			bool LocalBuffer::readPinnedData(void *userMem, unsigned long size) {

				//pinned memory format should be the same as the format of local memory

				BufferManager* bufMgr = Runtime::getInstance()->getBufferManager();
                assert(bufMgr);
                ProgramManager* progMgr = Runtime::getInstance()->getProgramManager();
                assert(progMgr);

                Buffer *pinnedBuf = 
                    bufMgr->createPinnedBuffer(_device, _dataFormat, _width, _height, userMem);

				if(!pinnedBuf)
				{
					LOG_COMMON_ERROR("calResCreate2D failed when writing back\n");
					return false;
				}

				CALcontext ctx = _device->getContext();
                assert(ctx);

				CALresult result;
                // Get the memory handle
                CALmem srcMem;
                CALmem dstMem;
                result = calCtxGetMem(&srcMem, ctx, pinnedBuf->getResHandle());
                CHECK_CAL_RESULT_ERROR(result, "Failed to get host memory handle \n");
                result = calCtxGetMem(&dstMem, ctx, _res);
                CHECK_CAL_RESULT_ERROR(result, "Failed to get local memory handle \n");

				CALevent memcpyEvent;
                result = calMemCopy(&memcpyEvent, ctx, srcMem, dstMem, 0);
                CHECK_CAL_RESULT_ERROR(result, "Failed to do DMA transfer.\n");

				int counter = 0;
				while(calCtxIsEventDone(ctx, memcpyEvent) == CAL_RESULT_PENDING) 
				{
					counter++;
				}

				calCtxReleaseMem(ctx, srcMem);
                CHECK_CAL_RESULT_ERROR(result, "Failed to release host memory handle \n");
                calCtxReleaseMem(ctx, dstMem);
                CHECK_CAL_RESULT_ERROR(result, "Failed to release local memory handle \n");
                bufMgr->destroyBuffer(pinnedBuf);

				return true;

			}

			//////////////////////////////////////////////////////////////////////////
            //!
            //! \param	ptr     The CPU address where that data in buffer will be 
            //!                 transfered to.
            //! \param	size    The size in bytes of the space the pointer points to.
            //! \return	bool    True if data transfer is succeeded. False if there is 
            //!                 an error during data transfer.
            //!
            //! \brief	Synchronized data transfer from GPU local memory to CPU memory.
            //!         Instead of DMA, copy kernel and pinned memory are used to have the peak 
            //!         performance.
            //!
            //////////////////////////////////////////////////////////////////////////
			bool LocalBuffer::writePinnedData(void *userMem, unsigned long size) {

				//TODO: only float 4 is supported now
				/*
				unsigned int height = _height * 4;
				if(size<height*_width*sizeof(float)) {
					LOG_COMMON_ERROR("calResCreate2D failed when writing back\n");
					return false;
				}
				*/

				BufferManager* bufMgr = Runtime::getInstance()->getBufferManager();
                assert(bufMgr);

                Buffer *pinnedBuf = 
                    bufMgr->createPinnedBuffer(_device, _dataFormat, _width, _height, userMem);

				if(!pinnedBuf)
				{
					LOG_COMMON_ERROR("calResCreate2D failed when writing back\n");
					return false;
				}

				Event* e = bufMgr->copy(this, pinnedBuf, this->_device);
                assert(e);
                if (e)
                {
                    e->waitEvent();
                }
                
                bufMgr->destroyBuffer(pinnedBuf);
                return true;
			}
        }
    }
}
