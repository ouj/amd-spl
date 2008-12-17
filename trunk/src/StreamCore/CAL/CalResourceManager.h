#ifndef _AMDSPL_CALRESOURCEMGR_
#define _AMDSPL_CALRESOURCEMGR_

#pragma once

class SPLCalDevice;
class SPLCalBuffer;

namespace amdspl
{
    class SPLCalResourceManager
    {
    public:
        SPLCalResourceManager(void);
        virtual ~SPLCalResourceManager(void);

        SPLCalBuffer*  createBuffer(unsigned short rank, unsigned int* dimensions, SPLCalDevice* device);
        void        destroyBuffer(SPLCalBuffer* buffer);
    };
}

#endif // _AMDSPL_CALRESMGR_