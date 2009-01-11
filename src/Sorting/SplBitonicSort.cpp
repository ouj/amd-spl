#include "SplBitonicSort.h"
#include "BitonicSortImpl.h"
#include "cal.h"
#include "calcl.h"
#include "CALDevice.h"
#include "CALRuntime.h"
#include "CALProgram.h"
#include <cassert>

namespace amdspl
{
    namespace sorting
    {
        bool BitonicSort::sort(float *ptr, unsigned int size, bool asc)
        {
            return BitonicSortImpl::sort(ptr, size, asc);
        }

        bool BitonicSort::sort(int *ptr, unsigned int size, bool asc)
        {
            return BitonicSortImpl::sort(ptr, size, asc);
        }

        bool BitonicSort::sort(unsigned int *ptr, unsigned int size, bool asc)
        {
            return BitonicSortImpl::sort(ptr, size, asc);
        }

        bool BitonicSort::sort(double *ptr, unsigned int size, bool asc)
        {
            return BitonicSortImpl::sort(ptr, size, asc);
        }
    }
}