#include "stdio.h"
#include "BitonicSortTest.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T>
static void TestPtrSort(const vector<T> &arrayi)
{
    for (unsigned int size = 32; size <= BitonicSortTest::Length; size = size << 1)
    {
        printf("Test Size %16d\t", size);
        vector<T> vec(arrayi.begin(), arrayi.begin() + size);
        vector<T> svec(arrayi.begin(), arrayi.begin() + size);

        sort(svec.begin(), svec.end());
        printf("Ascend");
        if(amdspl::sorting::BitonicSort::sort(&vec[0], size) == SPL_RESULT_OK)
        {
            for (unsigned int j = 0; j < size; j++)
            {
                ASSERT_EQ(svec[j], vec[j]);
            }
            printf("...OK\t");
        }
        else
            printf("...Failed\t");

        reverse(svec.begin(), svec.end());
        printf("Descend");

        if(amdspl::sorting::BitonicSort::sort(&vec[0], size, false) == SPL_RESULT_OK)
        {
            for (unsigned int j = 0; j < size; j++)
            {
                ASSERT_EQ(svec[j], vec[j]);
            }
            printf("...OK\n");
        }
        else
            printf("...Failed\n");
    }
}

template<>
static void TestPtrSort<double>(const vector<double> &arrayi)
{
    unsigned int Length = 8192 * 2048;
    for (unsigned int size = 32; size <= Length; size = size << 1)
    {
        printf("Test Size %16d\t", size);
        vector<double> vec(arrayi.begin(), arrayi.begin() + size);
        vector<double> svec(arrayi.begin(), arrayi.begin() + size);

        sort(svec.begin(), svec.end());
        printf("Ascend");
        if(amdspl::sorting::BitonicSort::sort(&vec[0], size) == SPL_RESULT_OK)
        {
            for (unsigned int j = 0; j < size; j++)
            {
                ASSERT_EQ(svec[j], vec[j]);
            }
            printf("...OK\t");
        }
        else
            printf("...Failed\t");

        reverse(svec.begin(), svec.end());
        printf("Descend");

        if(amdspl::sorting::BitonicSort::sort(&vec[0], size, false) == SPL_RESULT_OK)
        {
            for (unsigned int j = 0; j < size; j++)
            {
                ASSERT_EQ(svec[j], vec[j]);
            }
            printf("...OK\n");
        }
        else
            printf("...Failed\n");
    }
}


TEST_F(BitonicSortTest, FloatPtrSort)
{
    vector<float>   arrayf(BitonicSortTest::Length);

    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < BitonicSortTest::Length; i++)
    {
        int r = rand();
        arrayf[i] = (float)r / INT_MAX;
    }
    TestPtrSort(arrayf);
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
    TestPtrSort(arrayi);
}

TEST_F(BitonicSortTest, UnsignedIntPtrSort)
{
    vector<unsigned int>   arrayi(BitonicSortTest::Length);

    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < BitonicSortTest::Length; i++)
    {
        int r = rand();
        arrayi[i] = r;
    }
    TestPtrSort(arrayi);
}

TEST_F(BitonicSortTest, DoublePtrSort)
{
    vector<double>   arrayi(BitonicSortTest::Length);

    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < BitonicSortTest::Length; i++)
    {
        int r = rand();
        arrayi[i] = (double)r / INT_MAX;
    }
    TestPtrSort(arrayi);
}