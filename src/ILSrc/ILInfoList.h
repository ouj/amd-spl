#ifndef _AMD_SPL_ILINFOLIST_
#define _AMD_SPL_ILINFOLIST_

namespace amdspl
{
    class NullILInfo;

    // ILInfoList
    template <class T, class U>
    struct ILInfoList
    {
        typedef T Head;
        typedef U Tail;
    };

    template <class TList, class T> struct Append;

    template <> struct Append<NullILInfo, NullILInfo>
    {
        typedef NullILInfo Result;
    };

    template <class T> struct Append<NullILInfo, T>
    {
        typedef ILInfoList<T,NullILInfo> Result;
    };

    template <class Head, class Tail>
    struct Append<NullILInfo, ILInfoList<Head, Tail> >
    {
        typedef ILInfoList<Head, Tail> Result;
    };

    template <class Head, class Tail, class T>
    struct Append<ILInfoList<Head, Tail>, T>
    {
        typedef ILInfoList<Head, 
            typename Append<Tail, T>::Result>
            Result;
    };


    template <class TList, unsigned int index,
        typename DefaultType = NullILInfo>
    struct ILInfoAt
    {
        typedef DefaultType Result;
    };

    template <class Head, class Tail, typename DefaultType>
    struct ILInfoAt<ILInfoList<Head, Tail>, 0, DefaultType>
    {
        typedef Head Result;
    };

    template <class Head, class Tail, unsigned int i, typename DefaultType>
    struct ILInfoAt<ILInfoList<Head, Tail>, i, DefaultType>
    {
        typedef typename 
            ILInfoAt<Tail, i - 1, DefaultType>::Result Result;
    };

};
#endif