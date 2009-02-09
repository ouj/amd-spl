//
//
//
//  @ Project : AMD-SPL
//  @ File Name : RemoteBuffer.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


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
                return true;
            }
            
        }
    }
}
