#ifndef _AMDSPL_BITONICSORT_IMPL_
#define _AMDSPL_BITONICSORT_IMPL_

#include "SplBitonicSort.h"
#include "BitonicSortIL.h"
#include "Utility.h"
#include "CALProgram.h"
#include "CALBase.h"
#include <cmath>

namespace amdspl
{
    namespace sorting
    {
        class BitonicSortImpl : public BitonicSort
        {
        private:
            BitonicSortImpl(void) {};
            ~BitonicSortImpl(void) {};

        public:
            template<class T>
            static bool sort(T *ptr, unsigned int size, bool asc);

        protected:
            template<class T>
            static bool sortNoneAT(T* ptr, unsigned int _size, bool asc);

            template<class T>
            static bool sortAT(T* ptr, unsigned int _size, bool asc);

            template<class T>
            static CALresult InitialBuffer(bool asc, CalBuffer * sorted1Buffer, 
                const CALdomain &rect);
        };
    }
};

#include "BitonicSortImplDef.h"

#endif

