//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		RemoteBuffer.cpp
//!	\date 		1:3:2009   15:15
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of RemoteBuffer class.
//!
//////////////////////////////////////////////////////////////////////////
#include "RuntimeDefs.h"
#include "RemoteBuffer.h"


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
            RemoteBuffer::RemoteBuffer(CALformat format, unsigned int width, unsigned int height)
                : Buffer(format, width, height), _cachable(false)
            {
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy the RemoteBuffer object.
            //!
            //////////////////////////////////////////////////////////////////////////      
            RemoteBuffer::~RemoteBuffer()
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
            bool RemoteBuffer::initialize()
            {
                DeviceManager* deviceMgr = Runtime::getInstance()->getDeviceManager();
                assert(deviceMgr);
                CALdevice* deviceHandles = deviceMgr->getDeviceHandles();
                if (!deviceHandles)
                {
                    return false;
                }
                CALuint deviceNum = deviceMgr->getDeviceNum();
                if (!deviceHandles || !deviceNum)
                {
                    return false;
                }

                if (_height == 0) // 1D
                {
                    CALresult result = calResAllocRemote1D(&_res, deviceHandles, deviceNum, 
                        _width, _dataFormat, CAL_RESALLOC_CACHEABLE);
                    CHECK_CAL_RESULT_ERROR(result, "Failed create 1D remote buffer\n");
                }
                else // 2D
                {
                    CALresult result = calResAllocRemote2D(&_res, deviceHandles, deviceNum, 
                        _width, _height, _dataFormat, CAL_RESALLOC_CACHEABLE);
                    CHECK_CAL_RESULT_ERROR(result, "Failed create 2D remote buffer\n");
                }
                return true;
            }
        }
    }
}
