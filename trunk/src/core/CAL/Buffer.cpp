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

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            void Buffer::readData(void *ptr, unsigned int size)
            {
            
            }
            
            void Buffer::writeData(void *ptr, unsigned int size)
            {
            
            }
            
            void Buffer::getResHandle()
            {
            
            }
            
            void Buffer::getFormat()
            {
            
            }
            
            void Buffer::getPitch()
            {
            
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
            
            Buffer::Buffer(CALformat format, unsigned int width, unsigned int height)
            {
            
            }
            
            bool Buffer::initialize()
            {
                return true;
            }
            
            void Buffer::getCPUPointer()
            {
            
            }
            
            void Buffer::releaseCPUPointer()
            {
            
            }
            
        }
    }
}
