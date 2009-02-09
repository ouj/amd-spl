(#ifndef _AMDSPL_RUNTIMEEFS_H_
#define _AMDSPL_RUNTIMEEFS_H_

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
    fprintf(stderr, msg);
    return false; \
}

#endif //_AMDSPL_RUNTIMEEFS_H_