#ifndef _SPL_SORT_H_
#define _SPL_SORT_H_

#ifdef AMD_SPL_EXPORT
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

namespace amdspl
{
    void EXPORT bitonicSort(int *ptr, unsigned int _size);
    void EXPORT bitonicSort(void *ptr, unsigned int _size, unsigned int stride);
}

#endif