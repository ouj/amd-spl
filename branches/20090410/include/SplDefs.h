#ifndef AMDSPL_DEFS_H_
#define AMDSPL_DEFS_H_
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		SplDefs.h
//!	\date 		1:3:2009   20:43
//!	\author		Jiawei Ou
//!	
//!	\brief		Definition of AMD-SPL.
//!
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//!
//! \brief The enum of all the possible return value of AMD-SPL functions.
//!
//////////////////////////////////////////////////////////////////////////
enum SPL_RESULT
{
	SPL_RESULT_OK = 0,
	SPL_RESULT_ERROR,
	SPL_RESULT_NOT_INITIALIZED,
    SPL_RESULT_INVALID_ARGUMENT,
    SPL_RESULT_BUFFER_ERROR,
    SPL_RESULT_PROGRAM_ERROR
};

//  The warning disables visual studio's
//  annoying habit of warning when using the standard set lib
#ifdef _WIN32
#pragma warning (disable : 4251)
#endif

#ifdef AMD_SPL_EXPORT
#define SPL_EXPORT __declspec(dllexport)
#else
#define SPL_EXPORT
#endif

#endif //AMDSPL_DEFS_H_
