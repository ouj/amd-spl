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


#include "CALConstBuffer.h"
#include "Utility.h"

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Constructor
//!
//! \param dimensions dimension of the Buffer
//! \param device Device associated to CALBuffer
//! \param format 
//!
////////////////////////////////////////////////////////////////////////////////

CALConstBuffer::CALConstBuffer(unsigned int* dimensions, CalDevice* device, CALformat format)
                              :CALBuffer(1, dimensions, format, BUFFER_HOST, 0, device),
                              _nBytes(0)
{
    unsigned int bufferBytes = getElementBytes();
    unsigned int totalBytes = dimensions[0] * bufferBytes;
    _data = new unsigned char[totalBytes];
    memset((void*)_data, 0, totalBytes);
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Method that tells const buffer that it is going to be reused
//!
////////////////////////////////////////////////////////////////////////////////

void
CALConstBuffer::reuse()
{
    // Set the previous data to 0
    memset((void*)_data, 0, _nBytes);
    _nBytes = 0;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Sets the cpu pointer data with constant values
//!
////////////////////////////////////////////////////////////////////////////////
void
CALConstBuffer::pushConstant(void* data, BRformat format, unsigned int count)
{
    unsigned short bytes = Utility::getElementBytes(format);
    unsigned short bufferBytes = getElementBytes();

    // initialize data and set number of bytes initialized
    if(bytes == bufferBytes)
    {
        memcpy(_data + _nBytes, data, bytes * count);
        _nBytes += bufferBytes * count;
    }
    else
    {
        for(unsigned int i = 0; i < count; ++i)
        {
            memcpy(_data + _nBytes, (char*)data + i * bytes, bytes);
            _nBytes += bufferBytes;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Transfer data from cpu pointer _data to GPU buffer
//!
////////////////////////////////////////////////////////////////////////////////

bool
CALConstBuffer::setDataToBuffer()
{
    CALuint pitch;
    void* data = getBufferPointerCPU(pitch);
    if(!data)
    {
        return false;
    }

    memcpy(data, _data, _nBytes);
    freeBufferPointerCPU();

    return true;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Destructor
//!
////////////////////////////////////////////////////////////////////////////////

CALConstBuffer::~CALConstBuffer()
{
    delete[] _data;
}

