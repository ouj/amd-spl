#ifndef _AMDSPL_CALCONSTBUFFER_H_
#define _AMDSPL_CALCONSTBUFFER_H_

#include "Formats.h"
#include "CALBuffer.h"

////////////////////////////////////////////////////////////////////////////////
//!
//! \class CALConstBuffer
//!
//! \brief CAL implementation of Constant Buffer.
//! It contains method for setting data on this buffer.
//! 
//! Construction - It is constructed by CALBufferMgr during kernel execution.
//! CALBufferMgr contains logic to avoid allocation/de-allocation of buffer.
//! 
//! Destruction - Destroyed by BufferMgr. Very likely in a usual program 
//! that only one constant buffer will be used in the whole program and 
//! it will be destroyed in the end.
//! 
////////////////////////////////////////////////////////////////////////////////
using namespace amdspl;

class CALConstBuffer
{
    public:

        CALConstBuffer(unsigned int* dimensions, CalDevice* device, CALformat format);
        void pushConstant(void* data, BRformat format, unsigned int count = 1);
        bool setDataToBuffer();
        void reuse();
        ~CALConstBuffer();

    private:
        //! \brief CAL creates a buffer of multiple constants. 
        // _data points to the corresponding CPU array.
        unsigned char* _data;

        //! \brief number of bytes in _data
        unsigned int _nBytes;

};

#endif //_AMDSPL_CALCONSTBUFFER_H_
