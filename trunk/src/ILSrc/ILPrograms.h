#ifndef _AMDSPL_IL_PROGRAMS_
#define _AMDSPL_IL_PROGRAMS_

#include "ILInfoList.h"
#include "ILProgInfo.h"

namespace amdspl
{
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