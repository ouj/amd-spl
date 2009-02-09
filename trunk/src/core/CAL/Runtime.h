//
//
//
//  @ Project : AMD-SPL
//  @ File Name : Runtime.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_RUNTIME_H)
#define _RUNTIME_H
#include "cal.h"

namespace amdspl
{
    typedef void(*MemoryHandler)();

	struct DEVICE_LIST_ITEM;
    namespace core
    {
        namespace cal
        {
			class DeviceManager;
			class BufferManager;
			class ProgramManager;
			class ConstBufferPool;
			
            class Runtime
            {
            public:
                static Runtime* getInstance();
				bool virtual create(DEVICE_LIST_ITEM *devices = 0, unsigned short numDevices = 0);
                bool virtual destroy();
                DeviceManager* getDeviceManager();
                ConstBufferPool* getConstBufferPool();
                BufferManager* getBufferManager();
                ProgramManager* getProgramManager();
            private:
				Runtime();
				~Runtime();
                DeviceManager* _deviceMgr;
                ConstBufferPool* _constBufferPool;
                BufferManager* _bufferMgr;
                ProgramManager* _programMgr;
                static Runtime* _runtime;
                bool _shutdownOnDestroy;

                friend void atExitCleanUp();
            };
        }
    }
}

#endif  //_RUNTIME_H
