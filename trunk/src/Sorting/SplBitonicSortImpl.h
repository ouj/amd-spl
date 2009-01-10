#ifndef _AMDSPL_BITONICSORT_IMPL_
#define _AMDSPL_BITONICSORT_IMPL_

#include "SplBitonicSort.h"

namespace amdspl
{
    namespace sorting
    {
        class BitonicSortImpl : public BitonicSort
        {
        private:
            BitonicSortImpl(void);
            ~BitonicSortImpl(void);
        public:
            static bool bitonicSortImpl(float* ptr, unsigned int _size);
            static bool bitioncSortATImpl(float* ptr, unsigned int _size);
        };
    }
}

#endif

