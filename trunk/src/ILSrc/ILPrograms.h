#ifndef _AMDSPL_IL_PROGRAMS_
#define _AMDSPL_IL_PROGRAMS_

#include "ILProgInfo.h"

namespace amdspl
{
    enum ILPROGRAMS_INDEX
    {
        BITONIC_SORT_IL = 0,
		BITONIC_SORT_AT_IL,
        ILPRGROGRAMS_NUM
    };

    typedef ILProgInfo (*ILInfoFunc)(void);

    extern ILInfoFunc ILInfoFuncs[];
};


#endif //_AMDSPL_IL_PROGRAMS_