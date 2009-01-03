#include "amdspl.h"
#include "CALRuntime.h"
#include "CALProgram.h"
#include <assert.h>



namespace amdspl
{
	bool preInitProgram()
	{
        amdspl::CalRuntime::getInstance();
		return true;
	}
};