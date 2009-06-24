#ifndef AMDSPL_REMOTEBUFFER_H
#define AMDSPL_REMOTEBUFFER_H
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
#include "SplDefs.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	RemoteBuffer class is an abstract representation of CAL remote
            //!         buffer. It contains methods for remote buffer initialization.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class SPL_EXPORT RemoteBuffer : public Buffer
            {
                friend class BufferManager;
            public:
                ~RemoteBuffer();
            protected:
                RemoteBuffer(CALformat format, unsigned int width, unsigned int height = 0, unsigned int flag = 0);
                virtual bool initialize();
            };
        }
    }
}

#endif  //AMDSPL_REMOTEBUFFER_H
