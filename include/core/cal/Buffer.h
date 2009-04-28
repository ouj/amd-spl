#ifndef AMDSPL_BUFFER_H
#define AMDSPL_BUFFER_H

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
#include "SplDefs.h"
#include "IBuffer.h"
namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Event;

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	Buffer class is an abstract representation of CAL buffer.
            //!         Buffer class is the base class of LocalBuffer and RemoteBuffer,
            //!         it provides functionalities required for Buffer creation and
            //!         data transfer. It maintains the CAL handles, buffer type, 
            //!         format and dimensional information of a buffer.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class SPL_EXPORT Buffer : public IBuffer
            {
                friend class BufferManager;
            public:
                virtual         ~Buffer();
                virtual bool    readData(void *ptr, unsigned long size);
                virtual bool    writeData(void *ptr, unsigned long size);
                inline CALresource  getResHandle();
                inline CALformat    getFormat();
                inline unsigned int getWidth();
                inline unsigned int getHeight();

                unsigned int    getPitch();
                bool            setInputEvent(Event* e);
                bool            setOutputEvent(Event* e);
                void            waitInputEvent();
                void            waitOutputEvent();

                inline bool     isGlobal();
            protected:
                                Buffer(CALformat format, unsigned int width, 
                                    unsigned int height = 0, unsigned int flag = 0);
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
                //! \brief	Buffer initialization flag
                unsigned int    _flag;
            };

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CALresource
            //!
            //! \brief	Get the CAL resouce handle of the buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            CALresource Buffer::getResHandle()
            {
                return _res;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CALformat
            //!
            //! \brief	Get the CAL format of the buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            CALformat Buffer::getFormat()
            {
                return _dataFormat;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	unsigned int
            //!
            //! \brief	Get the width of the buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            unsigned int Buffer::getWidth()
            {
                return _width;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	unsigned int
            //!
            //! \brief	Get the height of the buffer, return 0 if it is a 1D buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            unsigned int Buffer::getHeight()
            {
                return _height;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool boolean value indicate whether this buffer is a global 
            //!         buffer.
            //!
            //! \brief	Check if the buffer is a global buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Buffer::isGlobal()
            {
                return _flag || CAL_RESALLOC_GLOBAL_BUFFER;
            }
        }
    }
}

#endif  //AMDSPL_BUFFER_H
