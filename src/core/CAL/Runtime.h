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
                static void destroy();
                DeviceManager* getDeviceManager();
                ConstBufferPool* getConstBufferPool();
                BufferManager* getBufferManager();
                ProgramManager* getProgramManager();
            private:
				Runtime();
				~Runtime();

                bool virtual create();
                
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
