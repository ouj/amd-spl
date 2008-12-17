#ifndef _AMDSPL_CALBUFFER_H_
#define _AMDSPL_CALBUFFER_H_

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

////////////////////////////////////////////////////////////////////////////////
//!
//! \file CALBuffer.h
//!
//! \brief Contains the declaration of CALBuffer class
//!
////////////////////////////////////////////////////////////////////////////////

#include "cal.h"

class CalDevice;

////////////////////////////////////////////////////////////////////////////////
//!
//! \enum BufferPool
//!
//! \brief Showing location of Buffer.
//!
////////////////////////////////////////////////////////////////////////////////

enum BufferPool
{
    BUFFER_LOCAL,   //GPU local side Buffer
    BUFFER_HOST     //Host side Buffer. Creation through CAL API

};


////////////////////////////////////////////////////////////////////////////////
//!
//! \class CALBuffer
//!
//! \brief CAL Backend specific implementation of Buffer.
//! Represnt both GPU local side or host side Buffer.
//! 
//! Its a wrapper around all the functionalities provided by CAL resource.
//! 
//! It contains three events to make streamRead and KernelExecution asynchronous.
//! 1. CopyEvent - Associated with streamRead. 
//! Wait for it in streamWrite and kernelExecution.
//! 2. InputEvent - Associated with Kernel execution when 
//! the buffer is an input to kernel.
//! Wait for it before streamRead.
//! 3. OutputEvent - Associated with Kernel execution when 
//! the buffer is an output to kernel.
//! Wait for it before streamRead and streamWrite
//! 
///////////////////////////////////////////////////////////////////////////////

class CalBuffer
{
    public:

        CalBuffer(unsigned short rank, unsigned int* dimansions,
                    CALformat format, BufferPool bufferPool, CALuint flag,
                    CalDevice* device);
        bool initialize();
        bool flush();

        inline const CALmem getMemHandle() const;
        inline const CALformat getFormat() const;
        unsigned int getPitch();

        void* getBufferPointerCPU(CALuint& pitch);
        void freeBufferPointerCPU();

        bool copyAsync(CalBuffer* srcBuffer, CALevent* event) const;
        inline const unsigned short getRank() const;
        inline unsigned int* getDimensions() const;
        unsigned short getElementBytes() const;

        void ref();
        void unref();
        ~CalBuffer();

        void waitCopyEvent();
        void waitInputEvent();
        void waitOutputEvent();

        inline const CALevent getCopyEvent() const;
        inline const CALevent getInputEvent() const;
        inline const CALevent getOutputEvent() const;

        void setCopyEvent(CALevent* value);
        void setInputEvent(CALevent* value);
        void setOutputEvent(CALevent* value);

        bool operator==(const CalBuffer& other) const;
    protected:

        bool _isEqual(const CalBuffer& other) const;

    protected:

        //! \brief number of refernce to this buffer
        unsigned int _refCount;

        //! \brief Rank of Buffer
        unsigned short _rank;

        //! \brief Dimensions of Buffer
        unsigned int* _dimensions;

        //! \brief Device information as each GPU local memory is specific to a device
        CalDevice* _device;

    private:

        //! \brief Data formats supported in CAL backend. 
        //! This formats might be different from Brook supported data formats.
        //! e.g. there is no equivalent for BR_FORMAT_FLOAT_3.
        CALformat _dataFormat;

        //! \brief CAL specific handle for resources
        CALresource _res;

        //! \brief CAL specific memory handle
        CALmem _mem;

        //! \brief Location of Buffer
        //! CAL Backend supports GPU memory on Host side also.
        //! These features are backend specific.
        //! This feature might be useful for DMA.
        BufferPool _bufferPool;

        //! \brief flag needed to create buffer
        //! GLOBAL or CACHEABLE buffer
        CALuint _flag;

        //! pitch of the allocated buffer
        CALuint _pitch;

        //! \brief Event associated to streamRead
        CALevent* _copyEvent;

        //! \brief Event associated to kernel execution if this buffer was input to the kernel.
        CALevent* _inputEvent;

        //! \brief Event associated to kernel execution if this buffer was output to the kernel.
        CALevent* _outputEvent;

};

inline const
unsigned short
CalBuffer::getRank() const
{
    return _rank;
}

inline
unsigned int*
CalBuffer::getDimensions() const
{
    return _dimensions;
}


inline const 
CALmem 
CalBuffer::getMemHandle() const
{
    return _mem;
}

inline const 
CALformat
CalBuffer::getFormat() const
{
    return _dataFormat;
}

inline const
CALevent
CalBuffer::getCopyEvent() const
{
    if(_copyEvent)
    {
        return *_copyEvent;
    }

    return 0;
}

inline const
CALevent
CalBuffer::getInputEvent() const
{
    if(_inputEvent)
    {
        return *_inputEvent;
    }

    return 0;
}

inline const
CALevent
CalBuffer::getOutputEvent() const
{
    if(_outputEvent)
    {
        return *_outputEvent;
    }

    return 0;
}

#endif //_CALBUFFER_H_
