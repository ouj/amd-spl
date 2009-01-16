#ifndef _AMDSPL_CALBUFFER_H_
#define _AMDSPL_CALBUFFER_H_

////////////////////////////////////////////////////////////////////////////////
//!
//! \file CALBuffer.h
//!
//! \brief Contains the declaration of CALBuffer class
//!
////////////////////////////////////////////////////////////////////////////////
#include "CommonDefs.h"
#include "cal.h"
namespace amdspl
{
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

		static CalBuffer* createBuffer(unsigned short rank, unsigned int* dimensions, CALformat calFormat);
        static inline void destroyBuffer(CalBuffer *buffer);

        CalBuffer(unsigned short rank, unsigned int* dimansions,
            CALformat format, BufferPool bufferPool, CALuint flag,
            CalDevice* device);
        bool initialize();
        bool flush();

        void readData(const void* appPtr, unsigned int size = -1);
        void writeData(void *appPtr, unsigned int size = -1);

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

	inline void
		CalBuffer::destroyBuffer(CalBuffer *buffer)
	{
		SAFE_DELETE(buffer);
	}

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
}
#endif //_CALBUFFER_H_
