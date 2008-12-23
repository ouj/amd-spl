#include "SplSort.h"
#include "cal.h"
#include "calcl.h"
#include "CALBuffer.h"
#include "CALRuntime.h"
#include "CALBufferMgr.h"
#include <vector>

namespace amdspl
{
    void SPLSort::bitonicSort(int *ptr, unsigned int _size)
    {
        uint InputDim[] = {_size};
        CalBuffer *buffer = 
            amdspl::CalRuntime::getInstance()->getBufferMgr()->createBuffer(1, InputDim, CAL_FORMAT_INT_1);
        buffer->readData(ptr);

        amdspl::CalRuntime::getInstance()->getProgramMgr();


        std::vector<int> temp(_size);
        buffer->writeData(&temp[0]);
    }

}
