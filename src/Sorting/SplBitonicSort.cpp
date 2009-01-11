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
        bool BitonicSort::sort(float *ptr, unsigned int size, bool asc)
        {
            assert(ptr && size > 0);
            if(!ptr || size <= 0)
                return false;

            CalDevice* device = CalRuntime::getInstance()->getDevice();
            CALdeviceinfo info = device->getInfo();
            if (size <= info.maxResource1DWidth)
            {
                return BitonicSortImpl::sort(ptr, size, asc);
            }
            else
            {
                return BitonicSortImpl::sortAT(ptr, size, asc);
            }
        }

        bool BitonicSort::sort(int *ptr, unsigned int size, bool asc)
        {
            assert(ptr && size > 0);
            if(!ptr || size <= 0)
                return false;

            CalDevice* device = CalRuntime::getInstance()->getDevice();
            CALdeviceinfo info = device->getInfo();
            if (size <= info.maxResource1DWidth)
            {
                return BitonicSortImpl::sort(ptr, size, asc);
            }
            else
            {
                return BitonicSortImpl::sortAT(ptr, size, asc);
            }
        }

        //bool BitonicSort::bitonicSort(unsigned int *ptr, unsigned int size, bool asc)
        //{
        //    CalDevice* device = CalRuntime::getInstance()->getDevice();
        //    CALdeviceinfo info = device->getInfo();
        //    if (size <= info.maxResource1DWidth)
        //    {
        //        return BitonicSortImpl::bitonicSortImpl(ptr, size, asc);
        //    }
        //    else
        //    {
        //        return BitonicSortImpl::bitioncSortATImpl(ptr, size, asc);
        //    }
        //}
    }
}