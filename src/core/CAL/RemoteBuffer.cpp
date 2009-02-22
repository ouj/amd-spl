//
//
//
//  @ Project : AMD-SPL
//  @ File Name : RemoteBuffer.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#include "RuntimeDefs.h"
#include "RemoteBuffer.h"


namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            RemoteBuffer::RemoteBuffer(CALformat format, unsigned int width, unsigned int height)
                : Buffer(format, width, height)
            {
                
            }
            
            bool RemoteBuffer::initialize()
            {
                DeviceManager* deviceMgr = Runtime::getInstance()->getDeviceManager();
                assert(deviceMgr);
                CALdevice* deviceHandles = deviceMgr->getDeviceHandles();
                CALuint deviceNum = deviceMgr->getDeviceNum();
                if (!deviceHandles || !deviceNum)
                {
                    return false;
                }

                if (_height == 0) // 1D
                {
                    CALresult result = calResAllocRemote1D(&_res, deviceHandles, deviceNum, 
                        _width, _dataFormat, 0);
                    CHECK_CAL_RESULT_ERROR(result, "Failed create 1D remote buffer\n");
                }
                else // 2D
                {
                    CALresult result = calResAllocRemote2D(&_res, deviceHandles, deviceNum, 
                        _width, _height, _dataFormat, 0);
                    CHECK_CAL_RESULT_ERROR(result, "Failed create 2D remote buffer\n");
                }
                return true;
            }
            
        }
    }
}
