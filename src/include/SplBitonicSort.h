#ifndef _SPL_SORT_H_
#define _SPL_SORT_H_

#ifdef AMD_SPL_EXPORT
#define SPL_EXPORT __declspec(dllexport)
#else
#define SPL_EXPORT
#endif

namespace amdspl
{
    namespace sorting
    {
        class SPL_EXPORT BitonicSort
        {
        public:
            static bool bitonicSort(float *ptr, unsigned int _size);
        };
    }
}

#endif