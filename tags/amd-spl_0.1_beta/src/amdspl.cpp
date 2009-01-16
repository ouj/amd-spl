#include "amdspl.h"
#include "CALRuntime.h"
#include "CALProgram.h"
#include <assert.h>


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
	bool initialSPL()
	{
        amdspl::CalRuntime::getInstance();
		return true;
	}

    //////////////////////////////////////////////////////////////////////////
    //! \brief This the initialization function of the amd-spl library.
    //!
    //! This function should be the first function call of the amd-spl
    //! library. (Note: currently this function does nothing)
    //////////////////////////////////////////////////////////////////////////
    bool cleanupSPL()
    {
        return true;
    }
};