#pragma once
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
