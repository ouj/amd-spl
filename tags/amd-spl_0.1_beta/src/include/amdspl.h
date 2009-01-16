#ifndef _AMD_SPL_LIBRARY_
#define _AMD_SPL_LIBRARY_

////////////////////////////////////////////////////////////////////////////////
//!
//! \file amdspl.h
//!
//! \brief Contains declaration of the initialization function and cleanup 
//!        function. it also include headers that are necessary to run the SPL 
//!
////////////////////////////////////////////////////////////////////////////////

#include "SplBitonicSort.h"

#ifdef AMD_SPL_EXPORT
#define SPL_EXPORT __declspec(dllexport)
#else
#define SPL_EXPORT
#endif

//////////////////////////////////////////////////////////////////////////
//!
//! \brief The namespace of AMD-SPL
//!
//////////////////////////////////////////////////////////////////////////
namespace amdspl
{
    //////////////////////////////////////////////////////////////////////////
    //! \brief This the initialization function of the amd-spl library.
    //!
    //! This function should be the first function call of the amd-spl
    //! library. (Note: currently this function does nothing)
    //////////////////////////////////////////////////////////////////////////
	bool SPL_EXPORT initialSPL();

    //////////////////////////////////////////////////////////////////////////
    //! \brief This is the clean up function of the amd-spl library.
    //!
    //! This function should be the last function call of the amd-spl
    //! library. (Note: currently this function does nothing)
    //////////////////////////////////////////////////////////////////////////
    bool SPL_EXPORT cleanupSPL();
}

#endif