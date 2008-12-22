#include "SplSort.h"
#include "cal.h"
#include "calcl.h"
#include "CALBuffer.h"
#include "CALRuntime.h"

namespace amdspl
{
    void SPLSort::bitonicSort(int *ptr, unsigned int _size)
    {
        CalBuffer *buffer = 
            amdspl::CalRuntime::getInstance()->getBufferManager()->createBuffer(1, NULL, NULL);
    }

}
