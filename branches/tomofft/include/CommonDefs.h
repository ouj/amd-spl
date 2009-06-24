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

#endif //_COMMONDEFS_H_
