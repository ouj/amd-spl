#ifndef _AMDSPL_COMMONDEFS_H_
#define _AMDSPL_COMMONDEFS_H_

//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		CommonDefs.h
//!	\date 		1:3:2009   15:18
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains common defintion used in AMD-SPL development.
//!
//////////////////////////////////////////////////////////////////////////
#include "stdio.h"

//! \brief Define NULL pointer value
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

//! \brief	Defines safe delete macro.
#define SAFE_DELETE(ptr) \
    if ((ptr) != NULL) \
{ \
    delete ptr; \
    ptr = NULL; \
}

//! \brief	Defines error log macro. Output to standard error stream.
#define LOG_ERROR(msg) \
{ \
    fprintf(stderr, (msg)); \
}

//! \brief	Defines trace log macro. Output to standard output stream.
#define LOG_TRACE(msg) \
{\
    fprintf(stdout, (msg)); \
}

//! \brief	Defines condition checking macro. 
//!         Log to error stream on condition false.
#define CHECK_CONDITION(condition, msg) \
if (!(condition)) \
{ \
    fprintf(stderr, (msg)); \
    return false; \
}

//! \brief	Defines condition checking macro. 
//!         Log to error stream and return NULL on condition false
#define CHECK_CONDITION_PTR(condition, msg) \
    if (!(condition)) \
{ \
    fprintf(stderr, (msg)); \
    return NULL; \
}

//! \brief	Defines CALresult checking macro.
#define CHECK_CAL_RESULT(result) \
    if (result != CAL_RESULT_OK) \
{ \
    return false; \
}

//! \brief	Defines CALresult checking macro, 
//!         log to standard error stream on error.
#define CHECK_CAL_RESULT_ERROR(result, msg) \
    if (result != CAL_RESULT_OK) \
{ \
    fprintf(stderr, (msg)); \
    return false; \
}

//! \brief	Defines CALresult checking macro, 
//!         log to standard error stream and return NULL on error.
#define CHECK_CAL_RESULT_ERROR2(result, msg) \
    if (result != CAL_RESULT_OK) \
{ \
    fprintf(stderr, (msg)); \
    return NULL; \
}

//! \brief	Defines CALresult checking macro, 
//!         log to standard error stream on error, without return value.
#define LOG_CAL_RESULT_ERROR(result, msg) \
    if (result != CAL_RESULT_OK) \
{ \
    fprintf(stderr, (msg)); \
}

#endif //_COMMONDEFS_H_
