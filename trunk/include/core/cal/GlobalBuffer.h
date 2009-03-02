#if !defined(_GLOBALBUFFER_H)
#define _GLOBALBUFFER_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		GlobalBuffer.h
//!	\date 		1:3:2009   13:50
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of GlobalBuffer class.
//!
//////////////////////////////////////////////////////////////////////////
#include "SplDefs.h"
#include "LocalBuffer.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	GlobalBuffer class is an abstract representation of CAL global
            //!         buffer using in memory export and scatter write.Contains 
            //!         initialization method of global buffer.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class SPL_EXPORT GlobalBuffer : public LocalBuffer
            {
                friend class BufferManager;
            public:
                ~GlobalBuffer();
            protected:
                GlobalBuffer(Device* device, CALformat format, 
                    unsigned int width, unsigned int height = 0);
                virtual bool initialize();
            };
        }
    }
}

#endif  //_GLOBALBUFFER_H
