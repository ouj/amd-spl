#include "CALBase.h"
#include "CALBufferMgr.h"
#include "CALBuffer.h"
#include "CALConstBuffer.h"
#include "CALDevice.h"
#include "Utility.h"

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Constructor
//!
//! \param device The device associated to a bufferMgr
//!
////////////////////////////////////////////////////////////////////////////////

CalBufferMgr::CalBufferMgr(CalDevice* device) :  _device(device)
{
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Method to create backend spefic buffers using CALBuffer.
//!
//! \param stream The associated stream
//! \return Pointer to the newly created buffer
//!
////////////////////////////////////////////////////////////////////////////////

CalBuffer*
CalBufferMgr::createBuffer(unsigned short rank, unsigned int* dimensions, CALformat calFormat)
{
    // Check if double precision is supported on the underlying hardware
    CALdeviceattribs attrib = _device->getAttribs();
    CALdeviceinfo info = _device->getInfo();

    if(!attrib.doublePrecision)
    {
        if(calFormat == CAL_FORMAT_DOUBLE_1 || calFormat == CAL_FORMAT_DOUBLE_2)
        {
            //stream->setErrorCode(BR_ERROR_NOT_SUPPORTED);
            //stream->setErrorString("Stream Allocation : Double precision not supported " 
            //    "on underlying hardware\n");

            return NULL;
        }
    }

    if(rank == 1 && dimensions[0] > info.maxResource1DWidth)
    {
        //stream->setErrorCode(BR_ERROR_NOT_SUPPORTED);
        //stream->setErrorString("Stream Allocation : This dimension not supported on undelying"
        //    "hardware\n");

        return NULL;
    }
    else if(rank == 2 && (dimensions[0] > info.maxResource2DWidth || 
        dimensions[1] > info.maxResource2DHeight))
    {
        //stream->setErrorCode(BR_ERROR_NOT_SUPPORTED);
        //stream->setErrorString("Stream Allocation : This dimension not supported on undelying"
        //    "hardware\n");

        return NULL;
    }

    CalBuffer* buffer = new CalBuffer(rank, dimensions, calFormat, 
        BUFFER_LOCAL, 0, _device);

    if (!buffer->initialize())
    {
        SAFE_DELETE(buffer);
        return NULL;
    }
    else
        return buffer;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Method to create CAL host buffers using CALBuffer.
//!
//! Uses a host resource cache to avoid allocation/ de-allocation
//!
//! \return Pointer to the newly created host buffer
//!
////////////////////////////////////////////////////////////////////////////////

CalBuffer* 
CalBufferMgr::createHostBuffer(unsigned short rank, unsigned int* dimensions,
                               const CALformat & format)
{
    CalBuffer* tmpBuffer = new CalBuffer(rank, dimensions, format, BUFFER_HOST,
        CAL_RESALLOC_CACHEABLE, _device);

    // Look into cache if a free resource exist of the same size
    unsigned int i = 0;
    CalBuffer* sameSizedBuffer = NULL;
    for(i = 0; i < _hostBufferCache.size(); ++i)
    {
        // Is size same?
        if(*_hostBufferCache[i] == *tmpBuffer)
        {
            // if size is same look if it is being used for another data transfer
            sameSizedBuffer = _hostBufferCache[i];
            CALevent copyEvent = sameSizedBuffer->getCopyEvent();
            CALevent inputEvent = sameSizedBuffer->getInputEvent();
            CALevent outputEvent = sameSizedBuffer->getOutputEvent();

            if(copyEvent == inputEvent == outputEvent == 0)
            {
                delete tmpBuffer;
                return sameSizedBuffer;
            }
        }
    }

    // Ceate if no free buffer in cache and push it in the cache
    if(!tmpBuffer->initialize())
    {
        // If same size buffer exist in cache. Wait for its events to finish
        // and return the same
        if(sameSizedBuffer)
        {
            sameSizedBuffer->waitCopyEvent();
            sameSizedBuffer->waitInputEvent();
            sameSizedBuffer->waitOutputEvent();

            delete tmpBuffer;

            return sameSizedBuffer;
        }
        else
        {
            // If there is no same sized buffer, wait for all the events 
            // associated to host resouces to finish and delete them.
            for(i = 0; i < _hostBufferCache.size(); ++i)
            {
                CalBuffer* buffer = _hostBufferCache[i];
                buffer->waitCopyEvent();
                buffer->waitInputEvent();
                buffer->waitOutputEvent();

                delete buffer;
            }

            _hostBufferCache.clear();

            // Try again to allocate resouce after deallocating all the resources
            if(!tmpBuffer->initialize())
            {
                delete tmpBuffer;

                return NULL;
            }
        }
    }

    // Keep it in a cache after creation
    _hostBufferCache.push_back(tmpBuffer);

    return tmpBuffer;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Method to clear used constant cache.
//!
//! This is used to avoid the case when same constant buffer is retuned for a
//! kernel invocation
//!
//!
////////////////////////////////////////////////////////////////////////////////

void
CalBufferMgr::clearUsedConstCache()
{
    _usedConstBuffers.clear();
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Method to create CALConstBuffer
//!
//! Uses a constant buffer cache to avoid allocation/ de-allocation
//!
//! \return Pointer to the newly created constant buffer
//!
////////////////////////////////////////////////////////////////////////////////

CalConstBuffer*
CalBufferMgr::createConstBuffer(unsigned int numConstants, CALformat calFormat)
{
    CALdeviceinfo info = _device->getInfo();
    if(numConstants > info.maxResource1DWidth)
    {
        return NULL;
    }

    // Try to use a nearest power 2 dimension so that we can 
    // cover cases when we need < 64 constant in a kernel(very likely)
    // with single constant buffer
    unsigned int size = amdspl::utils::ceilPow(numConstants);
    if(size == 0)
    {
        return NULL;
    }

    size = (size > 64) ? size : 64;

    unsigned int dimensions[] = {size};
    CalConstBuffer* tmpBuffer;

    tmpBuffer = new CalConstBuffer(dimensions, _device, calFormat);

    // Look into cache if a free resource exist of the same size
    unsigned int i = 0;
    CalConstBuffer* sameSizedBuffer = NULL;
    for(i = 0; i < _constBufferCache.size(); ++i)
    {
        // Is the size same?
        if(*_constBufferCache[i] == *tmpBuffer)
        {
            unsigned int j = 0;
            for(j = 0; j < _usedConstBuffers.size(); ++j)
            {
                if(_constBufferCache[i] == _usedConstBuffers[j])
                {
                    break;
                }
            }

            if(j == _usedConstBuffers.size())
            {
                sameSizedBuffer = _constBufferCache[i];
                CALevent inputEvent = sameSizedBuffer->getInputEvent();

                // If it is free, return it.
                if(inputEvent == 0)
                {
                    delete tmpBuffer;
                    sameSizedBuffer->reuse();
                    _usedConstBuffers.push_back(sameSizedBuffer);

                    return sameSizedBuffer;
                }
            }
        }
    }

    // Ceate if no free buffer in cache and push it in the cache
    if(!tmpBuffer->initialize())
    {
        // If same size buffer exist in cache. Wait for its events to finish
        // and return the same
        if(sameSizedBuffer)
        {
            sameSizedBuffer->waitInputEvent();
            delete tmpBuffer;
            sameSizedBuffer->reuse();
            _usedConstBuffers.push_back(sameSizedBuffer);

            return sameSizedBuffer;
        }
        else
        {
            // If there is no same sized buffer, wait for all the events 
            // associated to host resouces to finish and delete them.
            for(i = 0; i < _constBufferCache.size(); ++i)
            {
                CalConstBuffer* buffer = _constBufferCache[i];
                buffer->waitInputEvent();

                delete buffer;
            }

            _constBufferCache.clear();

            // Try again to allocate resouce after deallocating all the resources
            if(!tmpBuffer->initialize())
            {
                SET_ERROR("Failed to create host cal resource for constant buffer\n");
                delete tmpBuffer;

                return NULL;
            }
        }
    }

    _constBufferCache.push_back(tmpBuffer);
    _usedConstBuffers.push_back(tmpBuffer);

    return tmpBuffer;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Destructor
//! Delete data from caches for host buffer and constant buffer
//!
////////////////////////////////////////////////////////////////////////////////

CalBufferMgr::~CalBufferMgr()
{
    // Destroy all the host side and constant buffers available in cache
    for(unsigned int i = 0; i < _hostBufferCache.size(); ++i)
    {
        delete _hostBufferCache[i];
    }

    _hostBufferCache.clear();

    for(unsigned int i = 0; i < _constBufferCache.size(); ++i)
    {
        delete _constBufferCache[i];
    }

    for(unsigned int i = 0; i < _copyEvents.size(); ++i)
    {
        delete _copyEvents[i];
    }

}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Return an event that is not being used
//!
////////////////////////////////////////////////////////////////////////////////

CALevent* 
CalBufferMgr::getCopyEvent()
{
    // Look for a free event in the cache
    unsigned int i;
    for(i = 0; i < _copyEvents.size(); ++i)
    {
        if(*_copyEvents[i] == 0)
        {
            return _copyEvents[i];
        }
    }

    // Create if not found
    CALevent* event = new CALevent();
    *event = 0;
    _copyEvents.push_back(event);

    return event;
}

void CalBufferMgr::destroyBuffer(CalBuffer *buffer)
{

}