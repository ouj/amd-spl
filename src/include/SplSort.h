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
        static bool initModule(void);
        static bool bitonicSort(float *ptr, unsigned int _size);

	protected:
		static bool bitonicSortImpl(float* ptr, unsigned int _size);
		static bool bitioncSortATImpl(float* ptr, unsigned int _size, 
			unsigned int _width, unsigned int _height);
    };
}

#include "SplSortDef.h"

#endif