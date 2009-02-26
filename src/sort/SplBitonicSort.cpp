////////////////////////////////////////////////////////////////////////////////
//!
//! \file SplBitonicSort.cpp
//!
//! \brief Contains definition of BitonicSort
//!
////////////////////////////////////////////////////////////////////////////////

#include "SplBitonicSort.h"
#include "BitonicSortImpl.h"
#include "cal.h"
#include "calcl.h"
#include <cassert>

namespace amdspl
{
    namespace sorting
    {
        SPL_RESULT BitonicSort::sort(float *ptr, unsigned int size, bool asc)
        {
            return bionicSortImpl(ptr, size, asc);
        }

        SPL_RESULT BitonicSort::sort(int *ptr, unsigned int size, bool asc)
        {
            return bionicSortImpl(ptr, size, asc);
        }

        SPL_RESULT BitonicSort::sort(unsigned int *ptr, unsigned int size, bool asc)
        {
            return bionicSortImpl(ptr, size, asc);
        }

        SPL_RESULT BitonicSort::sort(double *ptr, unsigned int size, bool asc)
        {
            return bionicSortImpl(ptr, size, asc);
        }
    }
}