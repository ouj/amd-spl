#ifndef _AMDSPL_CALRESOURCEMGR_
#define _AMDSPL_CALRESOURCEMGR_

#pragma once

class CalDevice;
class CalBuffer;

namespace amdspl
{
    class CalResourceManager
    {
    public:
        CalResourceManager(void);
        virtual ~CalResourceManager(void);

        CalBuffer*  createBuffer(unsigned short rank, unsigned int* dimensions, CalDevice* device);
        void        destroyBuffer(CalBuffer* buffer);
    };
}

#endif // _AMDSPL_CALRESMGR_