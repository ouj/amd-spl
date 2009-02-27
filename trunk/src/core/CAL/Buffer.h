#if !defined(_BUFFER_H)
#define _BUFFER_H

//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		Buffer.h
//!	\date 		27:2:2009   15:51
//!	\author		Jiawei Ou
//!	
//!	\brief		Contain declaration of Buffer class.
//!
//////////////////////////////////////////////////////////////////////////

#include "cal.h"
namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Event;

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	Buffer class is the base class of LocalBuffer and RemoteBuffer,
            //!         it provides very low level functionalities required for Buffer 
            //!         creation and data transfer. It maintains the CAL handles, 
            //!         buffer type, format and dimensional information of a buffer.
            //! \warning Not Thread Safe!
            //!
            //////////////////////////////////////////////////////////////////////////
            class Buffer
            {
                friend class BufferManager;
            public:
                virtual         ~Buffer();
                virtual bool    readData(void *ptr, unsigned long size, void *defaultVal = 0);
                virtual bool    writeData(void *ptr, unsigned long size);
                CALresource     getResHandle();
                CALformat       getFormat();
                unsigned int    getPitch();
                unsigned int    getWidth();
                unsigned int    getHeight();

                bool            setInputEvent(Event* e);
                bool            setOutputEvent(Event* e);
                void            waitInputEvent();
                void            waitOutputEvent();
            protected:
                                Buffer(CALformat format, unsigned int width, unsigned int height = 0);
                virtual bool    initialize();
                void*           getPointerCPU(CALuint &pitch);
                void            releasePointerCPU();

                //! \brief	Store the CALformat of the buffer.
                CALformat       _dataFormat;
                //! \brief	Store the CALresource handle of the buffer.
                CALresource     _res;
                //! \brief	Store the width of the 1D or 2D buffer.
                unsigned int    _width;
                //! \brief	Store the height of 2D buffer. In the case of 1D buffer, 
                //!         height value is set to zero.
                unsigned int    _height;
                //! \brief	Store the pitch of buffer. Pitch value is acquired by calling 
                //          Buffer::getPointerCPU.
                CALuint         _pitch;
                //! \brief	Store the input event of the buffer.
                Event*          _inputEvent;
                //! \brief	Store the output event of the buffer.
                Event*          _outputEvent;
            };
        }
    }
}

#endif  //_BUFFER_H
