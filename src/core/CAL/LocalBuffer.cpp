//
//
//
//  @ Project : AMD-SPL
//  @ File Name : LocalBuffer.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//

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
            LocalBuffer::LocalBuffer(Device *device, CALformat format, unsigned int width, unsigned int height)
                : Buffer(format, width, height), _device(device)
            {
            }

            LocalBuffer::~LocalBuffer()
            {
            }

            //void LocalBuffer::readData(void* ptr, unsigned int size)
            //{
            //}
            //
            //void LocalBuffer::writeData(void* ptr, unsigned int size, void* defaultVal)
            //{
            //}
            
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
