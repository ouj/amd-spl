#ifndef _SPL_SORT_H_
#define _SPL_SORT_H_

////////////////////////////////////////////////////////////////////////////////
//!
//! \file SplBitonicSort.h
//!
//! \brief Contains declaration of BitonicSort
//!
////////////////////////////////////////////////////////////////////////////////

#ifdef AMD_SPL_EXPORT
#define SPL_EXPORT __declspec(dllexport)
#else
#define SPL_EXPORT
#endif

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
        //! \brief The class for bitonic sort.
        //!
        //////////////////////////////////////////////////////////////////////////
        class SPL_EXPORT BitonicSort
        {
        public:
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief Sort float point values in system memory
            //!
            //! \param ptr The float pointer points to a continuous memory
            //! \param size The size of the continuous memory
            //! \param asc The boolean value indicate that whether 
            //!         to sort the memory ascendantly
            //!
            //! \return Boolean value indicate whether the bitonic sort is successful
            //!
            //////////////////////////////////////////////////////////////////////////
            static bool sort(float *ptr, unsigned int size, bool asc = true);

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief Sort integer point values in system memory
            //!
            //! \param ptr The integer pointer points to a continuous memory
            //! \param size The size of the continuous memory
            //! \param asc The boolean value indicate that whether 
            //!         to sort the memory ascendantly
            //!
            //! \return Boolean value indicate whether the bitonic sort is successful
            //!
            //////////////////////////////////////////////////////////////////////////
            static bool sort(int *ptr, unsigned int size, bool asc = true);

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief Sort unsigned integer point values in system memory
            //!
            //! \param ptr The unsigned integer pointer points to a continuous memory
            //! \param size The size of the continuous memory
            //! \param asc The boolean value indicate that whether 
            //!         to sort the memory ascendantly
            //!
            //! \return Boolean value indicate whether the bitonic sort is successful
            //!
            //////////////////////////////////////////////////////////////////////////
            static bool sort(unsigned int *ptr, unsigned int size, bool asc = true);

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief Sort double point values in system memory
            //!
            //! \param ptr The double pointer points to a continuous memory
            //! \param size The size of the continuous memory
            //! \param asc The boolean value indicate that whether 
            //!         to sort the memory ascendantly
            //!
            //! \return Boolean value indicate whether the bitonic sort is successful
            //!
            //////////////////////////////////////////////////////////////////////////
            static bool sort(double *ptr, unsigned int size, bool asc = true);
        };
    }
}

#endif