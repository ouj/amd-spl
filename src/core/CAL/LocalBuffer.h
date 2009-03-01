#if !defined(_LOCALBUFFER_H)
#define _LOCALBUFFER_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		LocalBuffer.h
//!	\date 		1:3:2009   13:58
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of LocalBuffer class.
//!
//////////////////////////////////////////////////////////////////////////
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
            //! \brief	The abstract representation of CAL local buffer. Contains 
            //!         methods for local buffer initialization and optimized data 
            //!         transfer.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class LocalBuffer : public Buffer
            {
                friend class BufferManager;
            public:
                ~LocalBuffer();
            protected:
                LocalBuffer(Device* device, CALformat format, 
                    unsigned int width, unsigned int height = 0);
                virtual bool initialize();
                //! \brief	The pointer to the device object this local buffer associated to.
                Device* _device;
            };
        }
    }
}

#endif  //_LOCALBUFFER_H
