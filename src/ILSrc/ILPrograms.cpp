#include "ILPrograms.h"
#include "Sort_IL.h"

namespace amdspl
{
	typedef ILProgInfo (*ILInfoFunc)(void);
    ILInfoFunc ILInfoFuncs[] = 
    {
        &BitonicSortILInfo,
		&BitonicSortATILInfo
    };
}