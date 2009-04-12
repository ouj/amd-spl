#ifndef AMDSPL_CAL_COMMONDEFS_H
#define AMDSPL_CAL_COMMONDEFS_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		CalCommonDefs.h
//!	\date 		13:3:2009   14:13
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains macros needed in AMD-SPL compilation.
//!
//////////////////////////////////////////////////////////////////////////

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

#endif //AMDSPL_CAL_COMMONDEFS_H