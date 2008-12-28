#include "CALConstBuffer.h"
#include "CALBase.h"
#include "CALDevice.h"
#include "Utility.h"

namespace amdspl
{
    CalConstBuffer::CalConstBuffer(unsigned int* dimensions, CalDevice* device, CALformat format) : 
        CalBuffer(1, dimensions, format, BUFFER_HOST, 0, device),
        _nElements(dimensions[0])
    {
        _elementBytes = getElementBytes();
        unsigned int totalBytes = dimensions[0] * _elementBytes;
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
        if (i < 0 || i >= _nElements)
        {
            return;
        }

        unsigned short bytes = amdspl::utils::getElementBytes(format);

        memcpy(_data + i * _elementBytes, data, bytes);
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

        memcpy(data, _data, _elementBytes * _nElements);
        freeBufferPointerCPU();

        return true;
    }
}