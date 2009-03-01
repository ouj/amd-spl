#ifndef _SPL_SORT_H_
#define _SPL_SORT_H_


//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		SplBitonicSort.h
//!	\date 		1:3:2009   20:34
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of BitonicSort
//!
//////////////////////////////////////////////////////////////////////////

#ifdef AMD_SPL_EXPORT
#define SPL_EXPORT __declspec(dllexport)
#else
#define SPL_EXPORT
#endif
#include "SplDefs.h"

namespace amdspl
{
    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief The namespace of sorting, sorting methods are defined in this 
    //! namespace
    //!
    //////////////////////////////////////////////////////////////////////////
    namespace sorting
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \class BitonicSort
        //!
        //! \brief The class for Bitonic sort.
        //!
        //////////////////////////////////////////////////////////////////////////
        class SPL_EXPORT BitonicSort
        {
        public:

            static SPL_RESULT sort(float *ptr, unsigned int size, bool asc = true);
            static SPL_RESULT sort(int *ptr, unsigned int size, bool asc = true);
            static SPL_RESULT sort(unsigned int *ptr, unsigned int size, bool asc = true);
            static SPL_RESULT sort(double *ptr, unsigned int size, bool asc = true);
        };
    }
}

#endif