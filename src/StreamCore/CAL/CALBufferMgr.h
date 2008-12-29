#ifndef _AMDSPL_CALBUFFERMGR_H_
#define _AMDSPL_CALBUFFERMGR_H_

////////////////////////////////////////////////////////////////////////////////
//!
//! \file CALBufferMgr.h
//!
//! \brief Contains the declaration of CALBufferMgr class
//!
////////////////////////////////////////////////////////////////////////////////

#include "cal.h"
#include <vector>
#include <map>
#include "CALBuffer.h"
    
class CALDevice;
class CALBuffer;

namespace amdspl
{

    class CalConstArrayBuffer;
    class CalConstBuffer;

    typedef std::map<CALBuffer*, bool> BufferMap;
    typedef BufferMap::iterator BufferMapIter;

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \class CALBufferMgr
    //!
    //! \brief Backend specific implementation of memory management.
    //! 
    //! Contains various optimization and logic for CAL parity for data transfer 
    //! and host buffer allocation/de-allocation.
    //! 
    //! Contains a cache of host resources. Try to use these host resources to-
    //! 1. Get asynchronous behavior in streamRead. 
    //! 2. Avoid allocation/de-allocation and
    //! 3. Avoid an error if host resource memory is full.
    //! 
    /////////////////////////////////////////////////////////////////////////////////

    class CalBufferMgr
    {
    public:

        explicit        CalBufferMgr(CalDevice* device);
        CalConstArrayBuffer* createConstArrayBuffer(unsigned int numConstants, CALformat calFormat = CAL_FORMAT_FLOAT_4);
        CalConstBuffer* createConstBuffer(unsigned int numConstants, CALformat calFormat = CAL_FORMAT_FLOAT_4);
        CalBuffer*      createBuffer(unsigned short rank, unsigned int* dimensions, CALformat calFormat); 
        void            destroyBuffer(CalBuffer *buffer);
        void            clearUsedConstCache();

        ~CalBufferMgr();

        CalBuffer* createHostBuffer(unsigned short rank, unsigned int* dimensions, 
            const CALformat & format);
        CALevent* getCopyEvent();

    private:

        enum
        {
            TileSize = 256
        };
        //! \brief A cache that keeps Buffer and their status.
        //! It is possible that a Stream exists but Buffer doesn't (Lazy creation of Buffer).
        //! It is also possible a Stream is deleted but a Buffer exists. 
        //! (Memory Management - avoiding allocation/deallocation of resources)
        BufferMap _bufferMap;

        //! \brief Device for which this BufferMgr works
        CalDevice* _device;

        //! \brief Array of copy events.
        //! The same event adddress is used for temporary host resouce and 
        //! local resource during data transfer.
        std::vector<CALevent*> _copyEvents;

        //! \brief Cache for host memory data management.
        std::vector<CalBuffer*> _hostBufferCache;

        //! \brief Cache containg constant buffers
        std::vector<CalConstArrayBuffer*> _constBufferCache;

        //! \brief constant buffers being used in the the same kernel
        std::vector<CalConstArrayBuffer*> _usedConstBuffers;
    };
}
#endif //_AMDSPL_CALBUFFERMGR_H_
