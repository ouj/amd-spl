#ifndef _AMDSPL_DEFS_H_
#define _AMDSPL_DEFS_H_

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
    SPL_RESULT_BUFFER_ERROR
};

#endif //_AMDSPL_DEFS_H_