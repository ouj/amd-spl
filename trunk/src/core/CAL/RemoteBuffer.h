#if !defined(_REMOTEBUFFER_H)
#define _REMOTEBUFFER_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		RemoteBuffer.h
//!	\date 		1:3:2009   15:12
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of RemoteBuffer class.
//!
//////////////////////////////////////////////////////////////////////////
#include "Buffer.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	The abstract representation of CAL remote buffer. It contains 
            //!         methods for remote buffer initialization.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class RemoteBuffer : public Buffer
            {
                friend class BufferManager;
            public:
                ~RemoteBuffer();
            protected:
                RemoteBuffer(CALformat format, unsigned int width, unsigned int height = 0);
                virtual bool initialize();
                //! \brief	Boolean value indicate whether the remote buffer is CPU cache-able.
                bool _cachable;
            };
        }
    }
}

#endif  //_REMOTEBUFFER_H
