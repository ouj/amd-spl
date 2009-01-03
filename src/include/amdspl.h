#ifndef _AMD_SPL_LIBRARY_
#define _AMD_SPL_LIBRARY_
#include "SplSort.h"
#include "ILProgramIndex.h"

#ifdef AMD_SPL_EXPORT
#define SPL_EXPORT __declspec(dllexport)
#else
#define SPL_EXPORT
#endif

namespace amdspl
{
	bool SPL_EXPORT preInitProgram(ILPROGRAMS_INDEX *progIdxs);
}

#endif