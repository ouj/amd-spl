#ifndef _AMDSPL_IL_PROGRAMS_
#define _AMDSPL_IL_PROGRAMS_

#include "ILInfoList.h"
#include "ILProgInfo.h"

namespace amdspl
{
    enum ILPROGRAMS_INDEX
    {
        BITONIC_SORT_IL = 0,
        BITONIC_SORT_AT_IL,
        ILPRGROGRAMS_NUM
    };

    typedef ILInfoList<
            ILParameters<1, 1, 3>, 
        ILInfoList<
            ILParameters<1, 1, 7>, 
            NullILInfo
        > 
    > 
    ILINFOLIST;

    extern const char* ILSources[]; 
};

#endif //_AMDSPL_IL_PROGRAMS_