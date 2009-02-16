//
//
//
//  @ Project : AMD-SPL
//  @ File Name : Buffer.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#include "Buffer.h"
#include "RuntimeDefs.h"
#include <stdio.h>

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            void Buffer::readData(void *ptr, unsigned int size)
            {
            
            }
            
            void Buffer::writeData(void *ptr, unsigned int size, void* defaultVal)
            {
            
            }
            
            CALresource Buffer::getResHandle()
            {
                return _res;
            }
            
            CALformat Buffer::getFormat()
            {
                return _dataFormat;
            }
            
            unsigned int Buffer::getPitch()
            {
                if(!_pitch)
                {
                    getPointerCPU(_pitch);
                    releasePointerCPU();
                }
                return _pitch;
            }
            
            unsigned int Buffer::getWidth()
            {
                return _width;
            }
            
            unsigned int Buffer::getHeight()
            {
                return _height;
            }
            
            void Buffer::getBufferType()
            {
                
            }
            
            Buffer::Buffer(CALformat format, unsigned int width, unsigned int height) :
                _dataFormat(format), _width(width), _height(height), 
                _res(0), _pitch(0), _mem(0)
            {
            
            }
            
            bool Buffer::initialize()
            {
                return true;
            }
            
            void* Buffer::getPointerCPU(CALuint &pitch)
            {
                void* bufferPtr;
                CALresult result = calResMap(&bufferPtr, &pitch,
                    _res, 0);

                if (CAL_RESULT_OK == result)
                {
                    LOG_ERROR("Failed to get CPU pointer\n");
                    return NULL;
                }
            }
            
            void Buffer::releasePointerCPU()
            {
                CALresult result = calResUnmap(_res);
                LOG_CAL_RESULT_ERROR(result, "Failed to unmap resource\n");
            }
            
        }
    }
}
