#ifndef _SORT_H_
#define _SORT_H_

namespace amdspl
{
    class Sort
    {
    public:
        Sort(void);
        virtual ~Sort(void);

         template<class T> static 
            void BitonicSort(T *ptr, unsigned int _size);

    };
}

#include "SortDef.h"

#endif