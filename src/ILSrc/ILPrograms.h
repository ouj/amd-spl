#ifndef _AMDSPL_IL_PROGRAMS_
#define _AMDSPL_IL_PROGRAMS_

#include "ILProgInfo.h"
namespace amdspl
{
    enum ILPROGRAMS_INDEX
    {
        BITONIC_SORT_IL = 0,
        ILPRGROGRAMS_NUM
    };

    ILProgInfo* ILProgInfos[ILPRGROGRAMS_NUM];
};


#endif //_AMDSPL_IL_PROGRAMS_