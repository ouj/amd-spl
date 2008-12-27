#include "CALConstBuffer.h"
#include "CALBase.h"
#include "CALDevice.h"
#include "Utility.h"

namespace amdspl
{
    CalConstBuffer::CalConstBuffer(unsigned int* dimensions, CalDevice* device, CALformat format) : 
        CalBuffer(1, dimensions, format, BUFFER_HOST, 0, device),
        _nBytes(dimensions[0])
    {
        unsigned int bufferBytes = getElementBytes();
        unsigned int totalBytes = dimensions[0] * bufferBytes;
        _data = new unsigned char[totalBytes];
        memset((void*)_data, 0, totalBytes);
    }

    

    CalConstBuffer::~CalConstBuffer()
    {
        delete[] _data;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Sets the cpu pointer data with constant values
    //!
    ////////////////////////////////////////////////////////////////////////////////
    void
        CalConstBuffer::setConstant(void* data, CALformat format, unsigned int i)
    {
        if (i < 0 || i >= _nBytes)
        {
            return;
        }

        unsigned short bytes = amdspl::utils::getElementBytes(format);
        unsigned short bufferBytes = getElementBytes();

        memcpy(_data + i * bufferBytes, data, bytes);
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
}