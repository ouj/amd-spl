#ifndef AMDSPL_PINNEDBUFFER_H
#define AMDSPL_PINNEDBUFFER_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		PinnedBuffer.h
//!	\date 		5:5:2009   15:12
//!	\author		Shawn Zhou
//!	
//!	\brief		Contains declaration of PinnedBuffer class.
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
			static PFNCALRESCREATE2D calResCreate2D = 0;
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	RemoteBuffer class is an abstract representation of CAL remote
            //!         buffer. It contains methods for remote buffer initialization.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class SPL_EXPORT PinnedBuffer : public Buffer
            {
                friend class BufferManager;
            public:
                ~PinnedBuffer();
            protected:
                PinnedBuffer(Device *device, CALformat format, unsigned int width, unsigned int height, void *userMem);
                virtual bool	   initialize();
				virtual bool    readData(void *ptr, unsigned long size);
                virtual bool    writeData(void *ptr, unsigned long size);
				//! \brief	The pointer to the device object this local buffer associated to.
                Device* _device;
				void *_mem;
            };
        }
    }
}

#endif  //AMDSPL_PINNEDBUFFER_H
