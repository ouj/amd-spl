#ifndef _AMD_SPL_LIBRARY_
#define _AMD_SPL_LIBRARY_
#include "SplBitonicSort.h"

#ifdef AMD_SPL_EXPORT
#define SPL_EXPORT __declspec(dllexport)
#else
#define SPL_EXPORT
#endif

namespace amdspl
{
	bool SPL_EXPORT preInitProgram();
}

#endif