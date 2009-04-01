#include "stdio.h"
#include "BitonicSortTest.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include "Perf.h"

using namespace std;

template<typename T>
static void TestPtrSortStress(const vector<T> &arrayi)
{
    CPerfCounter timer;
    for (unsigned int size = 32; size <= BitonicSortTest::Length; size = size << 1)
    {
        printf("Test Size %16d\t", size);
        vector<T> vec(arrayi.begin(), arrayi.begin() + size);

        timer.Reset();
        timer.Start();
        SPL_RESULT res = amdspl::sorting::BitonicSort::sort(&vec[0], size);
        timer.Stop();
        if (res == SPL_RESULT_OK)
        {
            printf("Time: %.10lf\n", timer.GetElapsedTime());
        }
        else
            printf("...Failed\n");
    }
}

template<>
static void TestPtrSortStress<double>(const vector<double> &arrayi)
{
    CPerfCounter timer;
    unsigned int Length = 8192 * 2048;
    for (unsigned int size = 32; size <= Length; size = size << 1)
    {
        printf("Test Size %16d\t", size);
        vector<double> vec(arrayi.begin(), arrayi.begin() + size);

        timer.Reset();
        timer.Start();
        SPL_RESULT res = amdspl::sorting::BitonicSort::sort(&vec[0], size);
        timer.Stop();
        if (res == SPL_RESULT_OK)
        {
            printf("Time: %.10lf\n", timer.GetElapsedTime());
        }
        else
            printf("...Failed\n");
    }
}

TEST_F(BitonicSortTest, FloatPtrSortPerf)
{
    vector<float>   arrayf(BitonicSortTest::Length);

    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < BitonicSortTest::Length; i++)
    {
        int r = rand();
        arrayf[i] = (float)r / INT_MAX;
    }
    TestPtrSortStress(arrayf);
}

TEST_F(BitonicSortTest, IntPtrSortPerf)
{
    vector<int>   arrayi(BitonicSortTest::Length);

    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < BitonicSortTest::Length; i++)
    {
        int r = rand();
        arrayi[i] = r;
    }
    TestPtrSortStress(arrayi);
}

TEST_F(BitonicSortTest, UnsignedIntPtrPerf)
{
    vector<unsigned int>   arrayi(BitonicSortTest::Length);

    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < BitonicSortTest::Length; i++)
    {
        int r = rand();
        arrayi[i] = r;
    }
    TestPtrSortStress(arrayi);
}

TEST_F(BitonicSortTest, DoublePtrSortPerf)
{
    vector<double>   arrayi(BitonicSortTest::Length);

    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < BitonicSortTest::Length; i++)
    {
        int r = rand();
        arrayi[i] = (double)r / INT_MAX;
    }
    TestPtrSortStress(arrayi);
}
