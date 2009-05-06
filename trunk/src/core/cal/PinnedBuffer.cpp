//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		PinnedBuffer.cpp
//!	\date 		5:5:2009   15:15
//!	\author		Shawn Zhou
//!	
//!	\brief		Contains definition of RemoteBuffer class.
//!
//////////////////////////////////////////////////////////////////////////
#include "RuntimeDefs.h"
#include "PinnedBuffer.h"


namespace amdspl
{
    namespace core
    {
        namespace cal
        {
			
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	format  The CAL format of the remote buffer.
            //! \param	width   The width of 1D/2D remote buffer.
            //! \param	height  The height of 2D remote buffer. For 1D remote buffer,
            //!                 this value should be set to zero.
            //! \return	Constructor
            //!
            //! \brief	Construct the RemoteBuffer object. The object will not be 
            //!         available until RemoteBuffer::initialize() is called.
            //!
            //////////////////////////////////////////////////////////////////////////
            PinnedBuffer::PinnedBuffer(Device *device, CALformat format, unsigned int width, unsigned int height, void *userMem)
                : Buffer(format, width, height), _device(device), _mem(userMem)
            {
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy the RemoteBuffer object.
            //!
            //////////////////////////////////////////////////////////////////////////      
            PinnedBuffer::~PinnedBuffer()
            {
            }


            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool True if the remote buffer is initialized successful. 
            //!         False if there is an error during initialization.
            //!
            //! \brief	Initialize the RemoteBuffer object.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool PinnedBuffer::initialize()
            {
				#ifdef ATI_OS_VISTA 
				if(((uintptr_t)_mem) & (0xfff)) {
					LOG_COMMON_ERROR("memory should be aligned!");
					return false;
				}
				#else
				if(((uintptr_t)_mem) & (0xff)) {
					LOG_COMMON_ERROR("memory should be aligned!");
					return false;
				}
				#endif

				if(!calResCreate2D) {
					if( calExtGetProc((CALextproc*)&calResCreate2D, CAL_EXT_RES_CREATE, "calResCreate2D") != CAL_RESULT_OK )
					{
						LOG_COMMON_ERROR("calGetProc failed\n");
						return false;
					}
					if( calResCreate2D == 0 )
					{
						LOG_COMMON_ERROR("NULL function pointer. calResCreate2D\n");
						return false;
					}
				}

				//TODO: now use float1 as default
				unsigned int size = sizeof(float) * _width * _height;
				CALresult result = calResCreate2D(&_res, _device->getHandle(), (CALvoid*)_mem, 
							_width, _height, CAL_FORMAT_FLOAT_1, CALuint(size), 0);

				if(result!= CAL_RESULT_OK)
				{
					LOG_COMMON_ERROR("calResCreate2D failed. \n");
					return false;
				}
                return true;
            }

			 bool PinnedBuffer::readData(void *ptr, unsigned long size) { return false; }

			 bool PinnedBuffer::writeData(void *ptr, unsigned long size) { return false; }
        }
    }
}


