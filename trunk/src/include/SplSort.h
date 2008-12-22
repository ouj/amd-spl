#ifndef _SPL_SORT_H_
#define _SPL_SORT_H_

#ifdef AMD_SPL_EXPORT
#define SPL_EXPORT __declspec(dllexport)
#else
#define SPL_EXPORT
#endif

namespace amdspl
{
    class SPL_EXPORT SPLSort
    {
    public:
        static void bitonicSort(int *ptr, unsigned int _size);
        static void bitonicSort(void *ptr, unsigned int _size, unsigned int stride);
    };
}

#include "SplSortDef.h"

#endif