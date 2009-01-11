#include "BitonicSortTest.h"
#include <vector>

using namespace std;

TEST(BitonicSortTest, NullPtrSort)
{
    float* fp = NULL;
    int* ip = NULL;
    ASSERT_FALSE(amdspl::sorting::BitonicSort::bitonicSort(fp, 32));
    ASSERT_FALSE(amdspl::sorting::BitonicSort::bitonicSort(ip, 32));
}

TEST(BitonicSortTest, EmptySizeSort)
{
    vector<float> f(32);
    vector<int> i(32);
    float* fp = &f[0];
    int* ip = &i[0];
    ASSERT_FALSE(amdspl::sorting::BitonicSort::bitonicSort(fp, 0));
    ASSERT_FALSE(amdspl::sorting::BitonicSort::bitonicSort(ip, 0));
}

TEST(BitonicSortTest, NegateSizeSort)
{
    vector<float> f(32);
    vector<int> i(32);
    float* fp = &f[0];
    int* ip = &i[0];
    ASSERT_FALSE(amdspl::sorting::BitonicSort::bitonicSort(fp, -1));
    ASSERT_FALSE(amdspl::sorting::BitonicSort::bitonicSort(ip, -1));
}