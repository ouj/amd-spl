#if !defined(_CONSTBUFFER_H)
#define _CONSTBUFFER_H

//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		ConstBuffer.h
//!	\date 		28:2:2009   21:33
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of ConstBuffer class.
//!
//////////////////////////////////////////////////////////////////////////

#include "RemoteBuffer.h"
#include <vector>
#include "VectorDataType.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	ConstBuffer class is an abstract representation of a CAL 
            //!         constant buffer used in Program as a set input constants 
            //!         values. ConstBuffer class provides methods for setting data 
            //!         and data synchronization.
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class ConstBuffer : public RemoteBuffer
            {
                friend class BufferManager;
            public:
                ~ConstBuffer();
                template<unsigned int I, typename T>
                bool setConstant(T* pVal);
                bool sync();
            protected:
                ConstBuffer();
                bool resize(unsigned int size);
            private:
                //! \brief	The maximum size of constant buffer.
                enum
                {
                    MAX_CONST_NUM = 64
                };
                //! \brief	The system memory to store the constant value
                //!         before synchronize them to the constant buffer.
                std::vector<int4> _buffer;
            };
        }
    }
}

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \tparam I       Index of the constant value to be set.
            //! \tparam T       Type of the constant value.
            //! \param	pVal    The value of constant to be set.
            //! \return	bool    True if the constant value is successfully set. False  
            //!                 if there is an error during setting the constant value.
            //!
            //! \brief	Set the constant value. The value will be place in system 
            //!         memory, until ConstBuffer::sync() is called. 
            //!         
            //!
            //////////////////////////////////////////////////////////////////////////
            template<unsigned int I, typename T>
            bool ConstBuffer::setConstant(T* pVal)
            {
                if (sizeof(T) > sizeof(float4))
                {
                    return false;
                }
                T* ptr = (T*)&_buffer[I];
                *ptr = *pVal;
                return true;
            }
        }
    }
}

#endif  //_CONSTBUFFER_H
