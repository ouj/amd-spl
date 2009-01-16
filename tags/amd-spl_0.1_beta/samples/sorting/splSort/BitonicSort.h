#ifndef _AMDSPL_BITONICSORT_H_
#define _AMDSPL_BITONICSORT_H_

/*****************************************************************************
  \file PrefixSum.h
  \brief Contains the class definition for PrefixSum class
 ****************************************************************************/

#include "SampleBase.h"
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//!
//! \class  PrefixSum
//!
//! \brief  contains application properties for the sample prefix_sum
//! 
////////////////////////////////////////////////////////////////////////////////

class BitonicSort : public SampleBase
{
    public:

        BitonicSort(char* name);
        void allocateBuffer();
        void fillInputBuffer();
        int run();
        void printTimeInfo();
        void verifyResults();
        void comparePerformance();
        ~BitonicSort();

    private:

        unsigned int _lgArraySize;
        unsigned int _stage;
        vector<float>  _array1;
        vector<float>  _array2;
        vector<float>  _array3;
};

#endif // _PREFIXSUM_H_
