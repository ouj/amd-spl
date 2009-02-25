#ifndef _AMDSPL_COMMONDEFS_H_
#define _AMDSPL_COMMONDEFS_H_

#include "stdio.h"

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#define SAFE_DELETE(ptr) \
    if ((ptr) != NULL) \
{ \
    delete ptr; \
    ptr = NULL; \
}

#define LOG_ERROR(msg) \
{ \
    fprintf(stderr, (msg)); \
}

#define LOG_TRACE(msg) \
{\
    fprintf(stdout, (msg)); \
}

#define CHECK_CONDITION(condition, msg) \
if (!(condition)) \
{ \
    fprintf(stderr, (msg)); \
    return false; \
}

#define CHECK_CONDITION_PTR(condition, msg) \
    if (!(condition)) \
{ \
    fprintf(stderr, (msg)); \
    return NULL; \
}

#define CHECK_CAL_RESULT(result) \
    if (result != CAL_RESULT_OK) \
{ \
    return false; \
}

#define CHECK_CAL_RESULT_ERROR(result, msg) \
    if (result != CAL_RESULT_OK) \
{ \
    fprintf(stderr, (msg)); \
    return false; \
}

#define CHECK_CAL_RESULT_ERROR2(result, msg) \
    if (result != CAL_RESULT_OK) \
{ \
    fprintf(stderr, (msg)); \
    return NULL; \
}

#define LOG_CAL_RESULT_ERROR(result, msg) \
    if (result != CAL_RESULT_OK) \
{ \
    fprintf(stderr, (msg)); \
}
// An error
#define SET_ERROR(msg) \

#endif //_COMMONDEFS_H_
