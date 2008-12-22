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

CalConstBuffer::CalConstBuffer(unsigned int* dimensions, CalDevice* device, CALformat format)
                              :CalBuffer(1, dimensions, format, BUFFER_HOST, 0, device),
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
CalConstBuffer::reuse()
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
CalConstBuffer::pushConstant(void* data, BRformat format, unsigned int count)
{
    unsigned short bytes = amdspl::utils::getElementBytes(format);
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
CalConstBuffer::setDataToBuffer()
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

CalConstBuffer::~CalConstBuffer()
{
    delete[] _data;
}

