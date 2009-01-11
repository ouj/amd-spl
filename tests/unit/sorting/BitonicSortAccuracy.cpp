#include "StdAfx.h"
#include "BitonicSortTest.h"
#include <time.h>
#include <stdlib.h>
#include "stdio.h"
#include <algorithm>
#include <vector>

using namespace std;

TEST_F(BitonicSortTest, FloatPtrSort)
{
    vector<float>   arrayf(BitonicSortTest::Length);

    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < BitonicSortTest::Length; i++)
    {
        int r = rand();
        arrayf[i] = (float)r / INT_MAX;
    }

    for (unsigned int size = 32; size <= BitonicSortTest::Length; size = size << 1)
    {
        printf("Buffer size: %d: \n", size);
        vector<float> vec(arrayf.begin(), arrayf.begin() + size);
        vector<float> svec(arrayf.begin(), arrayf.begin() + size);

        sort(svec.begin(), svec.end());

        amdspl::sorting::BitonicSort::sort(&vec[0], size);
        
        for (unsigned int j = 0; j < size; j++)
        {
            ASSERT_EQ(svec[j], vec[j]);
        }
    }
}

TEST_F(BitonicSortTest, IntPtrSort)
{
    vector<int>   arrayi(BitonicSortTest::Length);

    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < BitonicSortTest::Length; i++)
    {
        int r = rand();
        arrayi[i] = r;
    }

    for (unsigned int size = 32; size <= BitonicSortTest::Length; size = size << 1)
    {
        printf("Buffer size: %d: \n", size);
        vector<int> vec(arrayi.begin(), arrayi.begin() + size);
        vector<int> svec(arrayi.begin(), arrayi.begin() + size);

        sort(svec.begin(), svec.end());

        amdspl::sorting::BitonicSort::sort(&vec[0], size);

        for (unsigned int j = 0; j < size; j++)
        {
            ASSERT_EQ(svec[j], vec[j]);
        }
    }
}