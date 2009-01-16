#include "BitonicSortTest.h"
#include <vector>

using namespace std;

TEST_F(BitonicSortTest, NullPtrSortFailure)
{
    float* fp = NULL;
    int* ip = NULL;
    ASSERT_FALSE(amdspl::sorting::BitonicSort::sort(fp, 32));
    ASSERT_FALSE(amdspl::sorting::BitonicSort::sort(ip, 32));
}

TEST_F(BitonicSortTest, EmptySizeSortFailure)
{
    vector<float> f(32);
    vector<int> i(32);
    float* fp = &f[0];
    int* ip = &i[0];
    ASSERT_FALSE(amdspl::sorting::BitonicSort::sort(fp, 0));
    ASSERT_FALSE(amdspl::sorting::BitonicSort::sort(ip, 0));
}

TEST_F(BitonicSortTest, NegateSizeSortFailure)
{
    vector<float> f(32);
    vector<int> i(32);
    float* fp = &f[0];
    int* ip = &i[0];
    ASSERT_FALSE(amdspl::sorting::BitonicSort::sort(fp, -1));
    ASSERT_FALSE(amdspl::sorting::BitonicSort::sort(ip, -1));
}