//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		GlobalBuffer.cpp
//!	\date 		1:3:2009   13:52
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of GlobalBuffer class.
//!
//////////////////////////////////////////////////////////////////////////
#include "GlobalBuffer.h"
#include "RuntimeDefs.h"
#include "Device.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	device  The pointer to the Device object this global buffer 
            //!                 associated to.
            //! \param	format  The CAL format of the global buffer.
            //! \param	width   The width of 1D/2D global buffer.
            //! \param	height  The height of 2D global buffer. For 1D global buffer,
            //!                 this value should be set to zero.
            //! \return	Constructor
            //!
            //! \brief	Construct the GlobalBuffer object. The object will not be 
            //!         available until GlobalBuffer::initialize() is called.
            //!
            //////////////////////////////////////////////////////////////////////////
            GlobalBuffer::GlobalBuffer(Device *device, CALformat format, unsigned int width, unsigned int height)
                : LocalBuffer(device, format, width, height)
            {
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy the GlobalBuffer object.
            //!
            //////////////////////////////////////////////////////////////////////////
            GlobalBuffer::~GlobalBuffer()
            {

            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool True if the global buffer is initialized successful. 
            //!         False if there is an error during initialization.
            //!
            //! \brief	Initialize the GlobalBuffer object.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool GlobalBuffer::initialize()
            {
                if (!_device)
                    return false;

                CALdeviceinfo info = _device->getInfo();
                if (_height == 0) // 1D
                {
                    if (_width > info.maxResource1DWidth)
                    {
                        return false;
                    }
                    CALresult result = calResAllocLocal1D(&_res, _device->getHandle(), 
                        _width, _dataFormat, CAL_RESALLOC_GLOBAL_BUFFER);
                    CHECK_CAL_RESULT_ERROR(result, "Failed create 1D buffer\n");
                }
                else // 2D
                {
                    if (_width > info.maxResource2DWidth || _height > info.maxResource2DHeight)
                    {
                        return false;
                    }
                    CALresult result = calResAllocLocal2D(&_res, _device->getHandle(), 
                        _width, _height, _dataFormat, CAL_RESALLOC_GLOBAL_BUFFER);
                    CHECK_CAL_RESULT_ERROR(result, "Failed create 2D buffer\n");
                }
                return true;
            }
        }
    }
}
