#ifndef _AMDSPL_CALBUFFER_AT_H_
#define _AMDSPL_CALBUFFER_AT_H_

////////////////////////////////////////////////////////////////////////////////
//!
//! \file CALBuffer.h
//!
//! \brief Contains the declaration of CALBuffer class
//!
////////////////////////////////////////////////////////////////////////////////
#include "CommonDefs.h"
#include "CALBuffer.h"
#include "cal.h"
namespace amdspl
{
    class CalDevice;

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

    class CalBufferAT : public CalBuffer
    {
    public:

        CalBufferAT(unsigned short logRank, unsigned int* logDimansions, 
            unsigned short bufferRan, unsigned int* bufferDimensions,
            CALformat format, BufferPool bufferPool, CALuint flag,
            CalDevice* device);

        ~CalBufferAT();
        unsigned short getBufferRank() const;
        unsigned int* getBufferDimensions() const;

    private:

        //! \brief Rank of the GPU buffer
        unsigned short _bufferRank;

        //! \brief Dimensions of the GPU buffer.
        unsigned int* _bufferDimensions;
    };
}
#endif //_CALBUFFER_H_
