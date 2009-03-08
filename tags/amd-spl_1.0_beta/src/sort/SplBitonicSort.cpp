//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		SplBitonicSort.cpp
//!	\date 		1:3:2009   20:35
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of BitonicSort
//!
//////////////////////////////////////////////////////////////////////////
#include "SplBitonicSort.h"
#include "BitonicSortImpl.h"
#include "cal.h"
#include "calcl.h"
#include <cassert>

namespace amdspl
{
    namespace sorting
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief Sort float point values in system memory
        //!
        //! \param ptr The float pointer points to a continuous memory
        //! \param size The size of the continuous memory
        //! \param asc The boolean value indicate that whether 
        //!         to sort the memory ascendantly
        //!
        //! \return	SPL_RESULT  
        //!                 \li SPL_RESULT_OK - if the array is sorted successfully.
        //!                 \li SPL_RESULT_INVALID_ARGUMENT - if the arguments passed 
        //!                 are invalid. 
        //!                 \li SPL_RESULT_BUFFER_ERROR - if there is an error happens
        //!                 during memory allocation or data transfer.
        //!                 \li SPL_RESULT_PROGRAM_ERROR - if there is an error in 
        //!                 program loading or execution.
        //!
        //////////////////////////////////////////////////////////////////////////
        SPL_RESULT BitonicSort::sort(float *ptr, unsigned int size, bool asc)
        {
            return bionicSortImpl(ptr, size, asc);
        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief Sort integer point values in system memory
        //!
        //! \param ptr The integer pointer points to a continuous memory
        //! \param size The size of the continuous memory
        //! \param asc The boolean value indicate that whether 
        //!         to sort the memory ascendantly
        //!
        //! \return	SPL_RESULT  
        //!                 \li SPL_RESULT_OK - if the array is sorted successfully.
        //!                 \li SPL_RESULT_INVALID_ARGUMENT - if the arguments passed 
        //!                 are invalid. 
        //!                 \li SPL_RESULT_BUFFER_ERROR - if there is an error happens
        //!                 during memory allocation or data transfer.
        //!                 \li SPL_RESULT_PROGRAM_ERROR - if there is an error in 
        //!                 program loading or execution.
        //!
        //////////////////////////////////////////////////////////////////////////
        SPL_RESULT BitonicSort::sort(int *ptr, unsigned int size, bool asc)
        {
            return bionicSortImpl(ptr, size, asc);
        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief Sort unsigned integer point values in system memory
        //!
        //! \param ptr The unsigned integer pointer points to a continuous memory
        //! \param size The size of the continuous memory
        //! \param asc The boolean value indicate that whether 
        //!         to sort the memory ascendantly
        //!
        //! \return	SPL_RESULT  
        //!                 \li SPL_RESULT_OK - if the array is sorted successfully.
        //!                 \li SPL_RESULT_INVALID_ARGUMENT - if the arguments passed 
        //!                 are invalid. 
        //!                 \li SPL_RESULT_BUFFER_ERROR - if there is an error happens
        //!                 during memory allocation or data transfer.
        //!                 \li SPL_RESULT_PROGRAM_ERROR - if there is an error in 
        //!                 program loading or execution.
        //!
        //////////////////////////////////////////////////////////////////////////
        SPL_RESULT BitonicSort::sort(unsigned int *ptr, unsigned int size, bool asc)
        {
            return bionicSortImpl(ptr, size, asc);
        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief Sort double point values in system memory
        //!
        //! \param ptr The double pointer points to a continuous memory
        //! \param size The size of the continuous memory
        //! \param asc The boolean value indicate that whether 
        //!         to sort the memory ascendantly
        //!
        //! \return	SPL_RESULT  
        //!                 \li SPL_RESULT_OK - if the array is sorted successfully.
        //!                 \li SPL_RESULT_INVALID_ARGUMENT - if the arguments passed 
        //!                 are invalid. 
        //!                 \li SPL_RESULT_BUFFER_ERROR - if there is an error happens
        //!                 during memory allocation or data transfer.
        //!                 \li SPL_RESULT_PROGRAM_ERROR - if there is an error in 
        //!                 program loading or execution.
        //!
        //////////////////////////////////////////////////////////////////////////
        SPL_RESULT BitonicSort::sort(double *ptr, unsigned int size, bool asc)
        {
            return bionicSortImpl(ptr, size, asc);
        }
    }
}