//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		LocalBuffer.cpp
//!	\date 		1:3:2009   14:05
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of LocalBuffer object.
//!
//////////////////////////////////////////////////////////////////////////
#include "RuntimeDefs.h"
#include "LocalBuffer.h"
#include "Device.h"
#include <stdio.h>

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	device  The pointer to the Device object this local buffer 
            //!                 associated to.
            //! \param	format  The CAL format of the local buffer.
            //! \param	width   The width of 1D/2D local buffer.
            //! \param	height  The height of 2D local buffer. For 1D local buffer,
            //!                 this value should be set to zero.
            //! \return	
            //!
            //! \brief	Construct the LocalBuffer object.The object will not be 
            //!         available until LocalBuffer::initialize() is called.
            //!
            //////////////////////////////////////////////////////////////////////////
            LocalBuffer::LocalBuffer(Device *device, CALformat format, unsigned int width, unsigned int height)
                : Buffer(format, width, height), _device(device)
            {
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy the LocalBuffer object.
            //!
            //////////////////////////////////////////////////////////////////////////
            LocalBuffer::~LocalBuffer()
            {
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool True if the local buffer is initialized successful. 
            //!         False if there is an error during initialization.
            //!
            //! \brief	Initialize the LocalBuffer object.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool LocalBuffer::initialize()
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
                        _width, _dataFormat, 0);
                    CHECK_CAL_RESULT_ERROR(result, "Failed create 1D buffer\n");
                }
                else // 2D
                {
                    if (_width > info.maxResource2DWidth || _height > info.maxResource2DHeight)
                    {
                        return false;
                    }
                    CALresult result = calResAllocLocal2D(&_res, _device->getHandle(), 
                        _width, _height, _dataFormat, 0);
                    CHECK_CAL_RESULT_ERROR(result, "Failed create 2D buffer\n");
                }
                return true;
            }
        }
    }
}
