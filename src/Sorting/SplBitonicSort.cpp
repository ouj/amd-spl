#include "SplBitonicSort.h"
#include "SplBitonicSortImpl.h"
#include "cal.h"
#include "calcl.h"
#include "CALDevice.h"
#include "CALRuntime.h"
#include "Sort_IL.h"
#include "CALProgram.h"
#include <cassert>

namespace amdspl
{
    namespace sorting
    {
        bool BitonicSort::bitonicSort(float *ptr, unsigned int _size)
        {
            CalDevice* device = CalRuntime::getInstance()->getDevice();
            CALdeviceinfo info = device->getInfo();
            if (_size <= info.maxResource1DWidth)
            {
                return BitonicSortImpl::bitonicSortImpl(ptr, _size);
            }
            else
            {
                return BitonicSortImpl::bitioncSortATImpl(ptr, _size);
            }
        }
    }
}