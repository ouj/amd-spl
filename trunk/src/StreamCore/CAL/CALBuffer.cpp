/****************************************************************************

Copyright (c) 2008, Advanced Micro Devices, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of Advanced Micro Devices, Inc nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

****************************************************************************/

#include "CALBase.h"
#include "CALBuffer.h"
#include "CALDevice.h"
#include "Runtime.h"
#include "BufferMgr.h"

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Constructor
//!
//! \param rank Rank of the Buffer
//! \param dimensions dimension os the Buffer
//! \param format Used CALformat for the buffer
//! \param bufferPool Location of the Buffer
//! \param device Device associated to CALBuffer
//!
////////////////////////////////////////////////////////////////////////////////

SPLCalBuffer::SPLCalBuffer(unsigned short rank, unsigned int* dimensions, 
                     CALformat format, BufferPool bufferPool, CALuint flag,
                     Device* device)
                     : Buffer(rank, dimensions, device),
                        _dataFormat(format), _res(0),
                        _mem(0), _bufferPool(bufferPool), _flag(flag), _pitch(0),
                        _copyEvent(NULL), _inputEvent(NULL), _outputEvent(NULL)
{
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Method where actual Buffer allocation happens on GPU 
//!
//! \return flag indicating whether Buffer allocation was successful or not
//!
////////////////////////////////////////////////////////////////////////////////

bool
SPLCalBuffer::initialize()
{
    SPLCalDevice* device = static_cast<SPLCalDevice*>(_device);
    CALdevice calDevice = device->getDevice();
    CALresult result;
    if(1 == _rank)
    {
        switch(_bufferPool)
        {
            case BUFFER_LOCAL:
                result = calResAllocLocal1D(&_res, calDevice, _dimensions[0], _dataFormat, _flag);
                break;
            case BUFFER_HOST:
                result = calResAllocRemote1D(&_res, &calDevice, 1, _dimensions[0], 
                                                _dataFormat, _flag);
                break;
        }
    }
    else if(2 == _rank)
    {
        switch(_bufferPool)
        {
            case BUFFER_LOCAL:
                result = calResAllocLocal2D(&_res, calDevice, _dimensions[0], _dimensions[1], _dataFormat, _flag);
                break;
            case BUFFER_HOST:
                result = calResAllocRemote2D(&_res, &calDevice, 1, _dimensions[0], _dimensions[1], 
                                                _dataFormat, _flag);
                break;
        }
    }

    CHECK_CAL_RESULT(result, "Failed to allocate resource \n");

    // Get the memory handle
    result = calCtxGetMem(&_mem, device->getContext(), _res);
    CHECK_CAL_RESULT(result, "Failed to get memory handle \n");

    return true;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Flush all the events associated to the buffer
//!
////////////////////////////////////////////////////////////////////////////////

bool
SPLCalBuffer::flush()
{
    waitCopyEvent();
    waitInputEvent();
    waitOutputEvent();

    return true;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Check the equality of two buffers
//!
////////////////////////////////////////////////////////////////////////////////

bool
SPLCalBuffer::_isEqual(const Buffer& other) const
{
    // Is base class properties same?
    bool flag = Buffer::_isEqual(other);

    // Check for data format equality if base class properties are same
    if(flag)
    {
        const SPLCalBuffer& buffer = static_cast<const SPLCalBuffer&>(other);

        return (_dataFormat == buffer.getFormat());
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Maps Buffer to a CPU addressible pointer
//!
//! \param pitch Pitch of the mapped memory
//! \return Pointer to the mapped memory
//!
////////////////////////////////////////////////////////////////////////////////

void*
SPLCalBuffer::getBufferPointerCPU(CALuint& pitch)
{
    void* bufferPtr;
    CALresult result = calResMap(&bufferPtr, &pitch, _res, 0);

    if(result != CAL_RESULT_OK)
    {
        SET_ERROR("Failed to map resource \n");
        return NULL;
    }

    return bufferPtr;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Frees mapped memory
//!
//! \param buffer CALBuffer to be unmapped
//!
////////////////////////////////////////////////////////////////////////////////

void
SPLCalBuffer::freeBufferPointerCPU()
{
    CALresult result = calResUnmap(_res);
    CAL_RESULT_LOG(result, "Failed to unmap resource \n");
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Get Pitch. CAL buffers allocated width is usually power of 2.
//!
////////////////////////////////////////////////////////////////////////////////

unsigned int
SPLCalBuffer::getPitch()
{
    if(!_pitch)
    {
        // The only way to get pitch is by mapping resouce to cpu pointer
        // This is costly, so we have cached the result in _pitch
        getBufferPointerCPU(_pitch);
        freeBufferPointerCPU();
    }

    return _pitch;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Function to copy data from srcBuffer to this Buffer.
//!
//! It is implemented using DMA
//!
//! \param srcBuffer Data to copy from
//! \param event event associated
//!
////////////////////////////////////////////////////////////////////////////////

bool
SPLCalBuffer::copyAsync(SPLCalBuffer* srcBuffer, CALevent* event) const
{
    SPLCalDevice* device = static_cast<SPLCalDevice*>(_device);
    CALcontext ctx = device->getContext();
    CALresult result = calMemCopy(event, ctx, 
                                    srcBuffer->getMemHandle(), 
                                    this->getMemHandle(), 0);

    CAL_RESULT_ERROR(result, "Failed to copy data \n");

    calCtxIsEventDone(ctx, *event);

    return true;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Decrease the ref count
//! Ask BufferMgr to destroy if refCount == 0 only if Buffer is local
//!
////////////////////////////////////////////////////////////////////////////////

void
SPLCalBuffer::unref()
{
    assert(_refCount > 0);

    if (--_refCount == 0)
    {
        waitInputEvent();
        waitOutputEvent();

        // That bufferMap is only for local resource
        if(_bufferPool == BUFFER_LOCAL)
        {
            ::brook::Runtime::getInstance()->getBufferMgr()->destroyBuffer(this);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Destructor
//!
////////////////////////////////////////////////////////////////////////////////

SPLCalBuffer::~SPLCalBuffer()
{
    SPLCalDevice* device = static_cast<SPLCalDevice*>(_device);

    // Destroy resource and release mem handle
    if(_res)
    {
        calCtxReleaseMem(device->getContext(), _mem);
    }

    if(_mem)
    {
        calResFree(_res);
    }
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Wait for the copy event to finish
//!
////////////////////////////////////////////////////////////////////////////////

void
SPLCalBuffer::waitCopyEvent()
{
    SPLCalDevice* device = static_cast<SPLCalDevice*>(_device);
    if(_copyEvent)
    {
        if(*_copyEvent != 0)
        {
            while(calCtxIsEventDone(device->getContext(), *_copyEvent))
                ;
            *_copyEvent = 0;
            _copyEvent = NULL;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Wait for the input event to finish
//!
////////////////////////////////////////////////////////////////////////////////

void
SPLCalBuffer::waitInputEvent()
{
    SPLCalDevice* device = static_cast<SPLCalDevice*>(_device);
    if(_inputEvent)
    {
        if(*_inputEvent != 0)
        {
            while(calCtxIsEventDone(device->getContext(), *_inputEvent))
                ;
            *_inputEvent = 0;
            _inputEvent = NULL;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Wait for the output event to finish
//!
////////////////////////////////////////////////////////////////////////////////

void
SPLCalBuffer::waitOutputEvent()
{
    SPLCalDevice* device = static_cast<SPLCalDevice*>(_device);
    if(_outputEvent)
    {
        if(*_outputEvent != 0)
        {
            while(calCtxIsEventDone(device->getContext(), *_outputEvent))
                ;
            *_outputEvent = 0;
            _outputEvent = NULL;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief set copy event value
//!
////////////////////////////////////////////////////////////////////////////////

void
SPLCalBuffer::setCopyEvent(CALevent* value)
{
    _copyEvent = value;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief set input event value
//!
////////////////////////////////////////////////////////////////////////////////

void
SPLCalBuffer::setInputEvent(CALevent* value)
{
    _inputEvent = value;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief set output event value
//!
////////////////////////////////////////////////////////////////////////////////

void
SPLCalBuffer::setOutputEvent(CALevent* value)
{
    _outputEvent = value;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Returns bytes in one element
//!
////////////////////////////////////////////////////////////////////////////////

unsigned short 
SPLCalBuffer::getElementBytes()const
{
    unsigned short numComponents = 0;
    unsigned short bytes = 0;

    switch(_dataFormat)
    {
        case CAL_FORMAT_FLOAT_1:
            numComponents = 1;
            bytes = sizeof(float);
            break;

        case CAL_FORMAT_UINT_1:
        case CAL_FORMAT_INT_1:
            numComponents = 1;
            bytes = sizeof(int);
            break;

        case CAL_FORMAT_DOUBLE_1:
            numComponents = 1;
            bytes = sizeof(double);
            break;

        case CAL_FORMAT_FLOAT_2:
            numComponents = 2;
            bytes = sizeof(float);
            break;

        case CAL_FORMAT_UINT_2:
        case CAL_FORMAT_INT_2:
            numComponents = 2;
            bytes = sizeof(int);
            break;

        case CAL_FORMAT_DOUBLE_2:
            numComponents = 2;
            bytes = sizeof(double);
            break;

        case CAL_FORMAT_FLOAT_4:
            numComponents = 4;
            bytes = sizeof(float);
            break;

        case CAL_FORMAT_UINT_4:
        case CAL_FORMAT_INT_4:
            numComponents = 4;
            bytes = sizeof(int);
            break;

        default:
            numComponents = 0;
            bytes = 0;
    }

    return numComponents * bytes;
}
