#include "amdspl.h"
#include "CALRuntime.h"
#include "CALProgram.h"
#include <assert.h>

#define PREINIT_PROGRAM(ID) case ID: \
{ CalProgram<ID>* program = CalProgram<ID>::getInstance();\
assert(program); if (!program) return false; break;}

namespace amdspl
{
	bool preInitProgram(ILPROGRAMS_INDEX *progIdxs)
	{
		if (progIdxs != NULL)
		{
			while(*progIdxs != ILPRGROGRAMS_NUM)
			{
                switch(*progIdxs)
                {
                    PREINIT_PROGRAM(BITONIC_SORT_IL)
                    PREINIT_PROGRAM(BITONIC_SORT_AT_IL)
                }
				progIdxs++;
			}
		}
		return true;
	}
};