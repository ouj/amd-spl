//
//
//
//  @ Project : AMD-SPL
//  @ File Name : GlobalBuffer.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#include "GlobalBuffer.h"
#include "RuntimeDefs.h"
#include "Device.h"



namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            GlobalBuffer::GlobalBuffer(Device *device, CALformat format, unsigned int width, unsigned int height)
                : LocalBuffer(device, format, width, height)
            {
            }

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
