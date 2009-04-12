//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		LocalBuffer.cpp
//!	\date 		1:3:2009   14:05
//!	\author		Jiawei Ou
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
            LocalBuffer::LocalBuffer(Device *device, CALformat format, unsigned int width, unsigned int height)
                : Buffer(format, width, height), _device(device)
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
                if (_height == 0) // 1D
                {
                    if (_width > info.maxResource1DWidth)
                    {
                        return false;
                    }
                    CALresult result = calResAllocLocal1D(&_res, _device->getHandle(), 
                        _width, _dataFormat, 0);
                    CHECK_CAL_RESULT_ERROR(result, "Failed create 1D buffer\n");
                }
                else // 2D
                {
                    if (_width > info.maxResource2DWidth || _height > info.maxResource2DHeight)
                    {
                        return false;
                    }
                    CALresult result = calResAllocLocal2D(&_res, _device->getHandle(), 
                        _width, _height, _dataFormat, 0);
                    CHECK_CAL_RESULT_ERROR(result, "Failed create 2D buffer\n");
                }
                return true;
            }

            bool LocalBuffer::readData(void *ptr, unsigned long size, void *defaultVal)
            {
#ifdef DMA_TRANSFER
                BufferManager* bufMgr = Runtime::getInstance()->getBufferManager();
                assert(bufMgr);

                Buffer *hostBuf = 
                    bufMgr->createRemoteBuffer(_dataFormat, _width, _height);
                if(!hostBuf)
                {
                    fprintf(stderr, "Failed to create host memory \n");
                    return false;
                }
                if(!hostBuf->readData(ptr, size, defaultVal))
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
                e->set(memcpyEvent, ctx);
                e->waitEvent();
                bufMgr->destroyBuffer(hostBuf);
#else
                Buffer::readData(ptr, size, defaultVal);
#endif // DMA_TRANSFER
                return true;
            }

            bool LocalBuffer::writeData(void *ptr, unsigned long size)
            {
#ifdef DMA_TRANSFER
                BufferManager* bufMgr = Runtime::getInstance()->getBufferManager();
                assert(bufMgr);

                Buffer *hostBuf = 
                    bufMgr->createRemoteBuffer(_dataFormat, _width, _height);
                if(!hostBuf)
                {
                    fprintf(stderr, "Failed to create host memory \n");
                    return false;
                }

                CALresult result = CAL_RESULT_OK;
                CALcontext ctx = _device->getContext();
                assert(ctx);

                // Get the memory handle
                CALmem srcMem;
                CALmem dstMem;
                result = calCtxGetMem(&dstMem, ctx, hostBuf->getResHandle());
                CHECK_CAL_RESULT_ERROR(result, "Failed to get host memory handle \n");
                result = calCtxGetMem(&srcMem, ctx, _res);
                CHECK_CAL_RESULT_ERROR(result, "Failed to get local memory handle \n");

                Event* e = 
                    Runtime::getInstance()->getProgramManager()->getEvent();

                CALevent memcpyEvent;
                result = calMemCopy(&memcpyEvent, ctx, srcMem, dstMem, 0);
                CHECK_CAL_RESULT_ERROR(result, "Failed to do DMA transfer.\n");
                e->set(memcpyEvent, ctx);
                e->waitEvent();
                if(!hostBuf->writeData(ptr, size))
                    return false;

                bufMgr->destroyBuffer(hostBuf);
#else
                Buffer::writeData(ptr, size);
#endif // DMA_TRANSFER
                return true;
            }
        }
    }
}
