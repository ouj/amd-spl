#include "CalResourceManager.h"
#include "stddef.h"

namespace amdspl
{
    CalResourceManager::CalResourceManager(void)
    {
    }

    CalResourceManager::~CalResourceManager(void)
    {
    }

    CalBuffer*  CalResourceManager::createBuffer(unsigned short rank, 
        unsigned int* dimensions, CalDevice* device)
    {
        return NULL;
    }

    void CalResourceManager::destroyBuffer(CalBuffer* buffer)
    {
        return;
    }
}

