#ifndef _AMDSPL_CALBASE_H_
#define _AMDSPL_CALBASE_H_

#include "CommonDefs.h"

// MACROS

// A problem that can be handled.
#define CHECK_CAL_RESULT(result, msg) \
if (result != CAL_RESULT_OK) \
{ \
    return false; \
}

// A problem that can be handled.
#define CAL_RESULT_ERROR(result, msg) \
if (result != CAL_RESULT_OK) \
{ \
    return false; \
}

#define CAL_RESULT_LOG(result, msg) \
if (result != CAL_RESULT_OK) \
{ \
}

#endif //_CALBASE_H_
