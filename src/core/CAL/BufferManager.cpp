//
//
//
//  @ Project : AMD-SPL
//  @ File Name : BufferManager.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#include "RuntimeDefs.h"

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
                SAFE_DELETE(buffer);
            }
            
            Buffer* BufferManager::createLocalBuffer(Device* device, CALformat format, unsigned int width, unsigned int height)
            {
                LocalBuffer *localBuf = new LocalBuffer(device, format, width, height);
                if (!localBuf->initialize())
                {
                    SAFE_DELETE(localBuf);
                    return NULL;
                }
                return localBuf;
            }

            Buffer* BufferManager::createGlobalBuffer(Device* device, CALformat format, unsigned int width, unsigned int height)
            {
                GlobalBuffer *globalBuf = new GlobalBuffer(device, format, width, height);
                if (!globalBuf->initialize())
                {
                    SAFE_DELETE(globalBuf);
                    return NULL;
                }
                return globalBuf;
            }

            Buffer* BufferManager::createRemoteBuffer(CALformat format, unsigned int width, unsigned int height)
            {
                RemoteBuffer *remoteBuf = new RemoteBuffer(format, width, height);
                if (!remoteBuf->initialize())
                {
                    SAFE_DELETE(remoteBuf);
                    return NULL;
                }
                return remoteBuf;
            }
            
        }
    }
}
