//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		ConstBuffer.cpp
//!	\date 		28:2:2009   21:56
//!	\author		
//!	
//!	\brief		Contains definition of ConstBuffer class.
//!
//////////////////////////////////////////////////////////////////////////
#include "ConstBuffer.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Constructor
            //!
            //! \brief	Construct the ConstBuffer object
            //!
            //////////////////////////////////////////////////////////////////////////
            ConstBuffer::ConstBuffer() : 
                RemoteBuffer(CAL_FORMAT_FLOAT_4, MAX_CONST_NUM, 0), _buffer(MAX_CONST_NUM)
            {
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	size    The new size of the constant buffer.
            //! \return	bool    True if the constant buffer is successfully resized.
            //!                 False if there is an error during the resizing.
            //!
            //! \brief	Resize the constant buffer. The new size cannot exceeded 
            //!         MAX_CONST_NUM.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool ConstBuffer::resize(unsigned int size)
            {
                if (size > MAX_CONST_NUM)
                {
                    fprintf(stderr, "Constant buffer size cannot exceed %d\n", MAX_CONST_NUM);
                    return false;
                }

                _buffer.resize(size);
                return true;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy the ConstBuffer object.
            //!
            //////////////////////////////////////////////////////////////////////////
            ConstBuffer::~ConstBuffer()
            {

            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool True if the constant values are successfully synchronized
            //!              to the CAL buffer. False if an error happens during 
            //!              data synchronization.
            //!
            //! \brief	Synchronize the constant values data in system memory to the
            //!         CAL buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool ConstBuffer::sync()
            {
                waitInputEvent();
                CALuint pitch;
                void* data = getPointerCPU(pitch);
                if(!data)
                {
                    return false;
                }
                memcpy(data, &_buffer[0], _buffer.size() * sizeof(float4));
                releasePointerCPU();
                return true;
            }
        }
    }
}
