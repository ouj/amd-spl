#ifndef _AMD_SPL_ILINFOLIST_
#define _AMD_SPL_ILINFOLIST_

#include "ILParaInfo.h"

namespace amdspl
{
    class ILParaEnd;

    // ILParaEnd
    template <class T, class U>
    struct ILPARA_LIST
    {
        typedef T Head;
        typedef U Tail;
    };

    template <class TList, class T> struct AppendILPara;

    template <> struct AppendILPara<ILParaEnd, ILParaEnd>
    {
        typedef ILParaEnd Result;
    };

    template <class T> struct AppendILPara<ILParaEnd, T>
    {
        typedef ILPARA_LIST<T,ILParaEnd> Result;
    };

    template <class Head, class Tail>
    struct AppendILPara<ILParaEnd, ILPARA_LIST<Head, Tail> >
    {
        typedef ILPARA_LIST<Head, Tail> Result;
    };

    template <class Head, class Tail, class T>
    struct AppendILPara<ILPARA_LIST<Head, Tail>, T>
    {
        typedef ILPARA_LIST<Head, 
            typename AppendILPara<Tail, T>::Result>
            Result;
    };


    template <class TList, unsigned int index,
        typename DefaultType = ILParaEnd>
    struct ILParaAt 
    {
        typedef DefaultType Result;
    };

    template <class Head, class Tail, typename DefaultType>
    struct ILParaAt<ILPARA_LIST<Head, Tail>, 0, DefaultType>
    {
        typedef Head Result;
    };

    template <class Head, class Tail, unsigned int i, typename DefaultType>
    struct ILParaAt<ILPARA_LIST<Head, Tail>, i, DefaultType>
    {
        typedef typename 
            ILParaAt<Tail, i - 1, DefaultType>::Result Result;
    };


    template <typename T, unsigned int id> struct ILParaByID;

    template <unsigned int id>
    struct ILParaByID<ILParaEnd, id>
    {
        typedef ILParaEnd Result;
    };

    template <class Tail, unsigned int id,
        unsigned int INPUT_NUM, 
        unsigned int OUTPUT_NUM, 
        unsigned int CONST_NUM,
        unsigned int CONST_ARRAY_NUM, 
        unsigned int SCATTER_NUM>
    struct ILParaByID<ILPARA_LIST<ILParaInfo<id, INPUT_NUM, OUTPUT_NUM, CONST_NUM, CONST_ARRAY_NUM, SCATTER_NUM>, Tail>, id>
    {
        typedef typename 
            ILParaInfo<id, INPUT_NUM, OUTPUT_NUM, CONST_NUM, CONST_ARRAY_NUM, SCATTER_NUM> Result;
    };

    template <class Head, class Tail, unsigned int id>
    struct ILParaByID<ILPARA_LIST<Head, Tail>, id>
    {
        typedef typename 
            ILParaByID<Tail, id>::Result Result;
    };

};
#endif