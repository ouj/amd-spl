#ifndef _BITONIC_SORT_TEST_H_
#define _BITONIC_SORT_TEST_H_

#include "gtest\gtest.h"
#include "SplBitonicSort.h"

using namespace std;

class BitonicSortTest : public testing::Test
{
protected:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static bool HasFatalFailure();

public:
    static unsigned int             Length;

private:
    static bool                     m_Fatal;
};
#endif