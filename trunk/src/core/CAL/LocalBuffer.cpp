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

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            void LocalBuffer::readData(void* ptr, unsigned int size)
            {
            
            }
            
            void LocalBuffer::writeData(void* ptr, unsigned int size)
            {
            
            }
            
            LocalBuffer::LocalBuffer(Device *device, CALformat format, unsigned int width, unsigned int height)
                : Buffer(format, width, height), _device(device)
            {
            
            }
            
            bool LocalBuffer::initialize()
            {
                return true;
            }
            
        }
    }
}
