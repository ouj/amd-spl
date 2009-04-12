#ifndef AMDSPL_LOCALBUFFER_H
#define AMDSPL_LOCALBUFFER_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		LocalBuffer.h
//!	\date 		1:3:2009   13:58
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of LocalBuffer class.
//!
//////////////////////////////////////////////////////////////////////////
#include "SplDefs.h"
#include "Buffer.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Device;
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	LocalBuffer class is an abstract representation of CAL local  
            //!         buffer. It contains methods for local buffer initialization 
            //!         and optimized data transfer.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class SPL_EXPORT LocalBuffer : public Buffer
            {
                friend class BufferManager;
            public:
                ~LocalBuffer();
            protected:
                LocalBuffer(Device* device, CALformat format, 
                    unsigned int width, unsigned int height = 0);
                virtual bool    initialize();
                virtual bool    readData(void *ptr, unsigned long size, void *defaultVal = 0);
                virtual bool    writeData(void *ptr, unsigned long size);
                //! \brief	The pointer to the device object this local buffer associated to.
                Device* _device;
            };
        }
    }
}

#endif  //_LOCALBUFFER_H
