#ifndef _AMDSPL_BITONICSORT_IMPL_
#define _AMDSPL_BITONICSORT_IMPL_

namespace amdspl
{
    class SplBitonicSortImpl
    {
    private:
        SplBitonicSortImpl(void);
        ~SplBitonicSortImpl(void);
    public:
        static bool bitonicSortImpl(float* ptr, unsigned int _size);
        static bool bitioncSortATImpl(float* ptr, unsigned int _size);
    };
}

#endif

