#include "CALBase.h"
#include "CALBuffer.h"
#include "CALDevice.h"
#include "CALRuntime.h"
#include "CALBufferAT.h"
#include <assert.h>
#include "cal.h"

namespace amdspl
{
    CalBufferAT::CalBufferAT(unsigned short logRank, unsigned int* logDimansions, 
        unsigned short bufferRank, unsigned int* bufferDimensions,
        CALformat format, BufferPool bufferPool, CALuint flag,
        CalDevice* device) : 
    CalBuffer(logRank, logDimansions, format, bufferPool, flag, device)
    {
        _bufferDimensions = new unsigned int[bufferRank];

        memcpy(_bufferDimensions, bufferDimensions, bufferRank * sizeof(unsigned int));
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the physical rank of the stream
    //!
    ////////////////////////////////////////////////////////////////////////////////

    unsigned short
        CalBufferAT::getBufferRank() const
    {
        return _bufferRank;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get Buffer Dimensions
    //!
    ////////////////////////////////////////////////////////////////////////////////

    unsigned int*
        CalBufferAT::getBufferDimensions() const
    {
        return _bufferDimensions;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Destructor
    //!
    ////////////////////////////////////////////////////////////////////////////////

    CalBufferAT::~CalBufferAT()
    {
        delete[] _bufferDimensions;
    }

}