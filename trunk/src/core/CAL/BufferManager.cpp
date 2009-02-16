//
//
//
//  @ Project : AMD-SPL
//  @ File Name : BufferManager.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#include "BufferManager.h"
#include "CommonDefs.h"
#include "LocalBuffer.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            BufferManager::BufferManager()
            {

            }
            
            BufferManager::~BufferManager()
            {

            }
            
            bool BufferManager::initialize()
            {
                return true;
            }

            void BufferManager::destroyBuffer(Buffer* buffer)
            {
            
            }
            
            Buffer* BufferManager::createLocalBuffer(Device* device, CALformat format, unsigned int width, unsigned int height)
            {
                LocalBuffer *localBuf = new LocalBuffer(device, format, width, height);
                return NULL;
            }

            Buffer* BufferManager::createScatterBuffer(Device* device, CALformat format, unsigned int width, unsigned int height)
            {
                return NULL;
            }

            Buffer* BufferManager::createRemoteBuffer(CALformat format, unsigned int width, unsigned int height)
            {
                return NULL;
            }
            
        }
    }
}
