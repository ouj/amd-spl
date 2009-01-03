#include "amdspl.h"
#include "CALRuntime.h"
#include "CALProgramMgr.h"
#include <assert.h>

namespace amdspl
{
	class CalProgram;
	bool preInitSPL(ILPROGRAMS_INDEX *progIdxs)
	{
		CalRuntime* runtime = amdspl::CalRuntime::getInstance();
		assert(runtime);
		if (!runtime)
		{
			return false;
		}

		CalProgramMgr* progMgr = runtime->getProgramMgr();
		assert(progMgr);
		if (!progMgr)
		{
			return false;
		}

		if (progIdxs != NULL)
		{
			const CalProgram *program = NULL;
			while(*progIdxs != ILPRGROGRAMS_NUM)
			{
				program = progMgr->GetProgram(*progIdxs);
				assert(program);
				if (!program)
				{
					return false;
				}
				progIdxs++;
			}
		}
		return true;
	}
};