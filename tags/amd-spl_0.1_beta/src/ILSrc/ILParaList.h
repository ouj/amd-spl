#ifndef _AMD_SPL_ILINFOLIST_
#define _AMD_SPL_ILINFOLIST_

#include "ILParaInfo.h"

namespace amdspl
{
    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief The end class of the program list
    //!
    //////////////////////////////////////////////////////////////////////////
    class ILParaEnd;

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Program list item
    //!
    //////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    struct ILPARA_LIST
    {
        typedef T Head;
        typedef U Tail;
    };

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Definition of AppendILPara
    //!
    //////////////////////////////////////////////////////////////////////////
    template <class TList, class T> struct AppendILPara;

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Append empty list to empty list
    //!
    //////////////////////////////////////////////////////////////////////////
    template <> struct AppendILPara<ILParaEnd, ILParaEnd>
    {
        typedef ILParaEnd Result;
    };

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Append a program to a empty list
    //!
    //////////////////////////////////////////////////////////////////////////
    template <class T> struct AppendILPara<ILParaEnd, T>
    {
        typedef ILPARA_LIST<T,ILParaEnd> Result;
    };

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Append a program list to an empty list.
    //!
    //////////////////////////////////////////////////////////////////////////
    template <class Head, class Tail>
    struct AppendILPara<ILParaEnd, ILPARA_LIST<Head, Tail> >
    {
        typedef ILPARA_LIST<Head, Tail> Result;
    };

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Append a program to a program list
    //!
    //////////////////////////////////////////////////////////////////////////
    template <class Head, class Tail, class T>
    struct AppendILPara<ILPARA_LIST<Head, Tail>, T>
    {
        typedef ILPARA_LIST<Head, 
            typename AppendILPara<Tail, T>::Result>
            Result;
    };

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Definition of ILParaByID
    //!
    //////////////////////////////////////////////////////////////////////////
    template <typename T, unsigned int id> struct ILParaByID;

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief The case that ID not match
    //!
    //////////////////////////////////////////////////////////////////////////
    template <unsigned int id>
    struct ILParaByID<ILParaEnd, id>
    {
        typedef ILParaEnd Result;
    };

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief The case that the program is found
    //!
    //////////////////////////////////////////////////////////////////////////
    template <class Tail, unsigned int id,
        unsigned int INPUT_NUM, 
        unsigned int OUTPUT_NUM, 
        unsigned int CONST_NUM,
        unsigned int CONST_ARRAY_NUM, 
        unsigned int SCATTER_NUM>
    struct ILParaByID<ILPARA_LIST<ILParaInfo<id, INPUT_NUM, OUTPUT_NUM, 
        CONST_NUM, CONST_ARRAY_NUM, SCATTER_NUM>, Tail>, id>
    {
        typedef typename 
            ILParaInfo<id, INPUT_NUM, OUTPUT_NUM, CONST_NUM, 
            CONST_ARRAY_NUM, SCATTER_NUM> Result;
    };

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief The case that the current item is not match, 
    //! 
    //! find the next recursively.
    //!
    //////////////////////////////////////////////////////////////////////////
    template <class Head, class Tail, unsigned int id>
    struct ILParaByID<ILPARA_LIST<Head, Tail>, id>
    {
        typedef typename 
            ILParaByID<Tail, id>::Result Result;
    };

};
#endif