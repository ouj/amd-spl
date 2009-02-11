#include "gtest\gtest.h"
#include "amdspl.h"
#include "Runtime.h"

using namespace amdspl;
using namespace amdspl::core::cal;

TEST(InitCleanUpFailureTests, InitFalure1Test)
{
    ASSERT_TRUE(AmdSpl::InitializeSPL(NULL, 0) == SPL_RESULT_INVALID_ARGUMENT);
}

TEST(InitCleanUpFailureTests, InitFalure2Test)
{
    ASSERT_TRUE(AmdSpl::InitializeSPL(NULL, 1) == SPL_RESULT_INVALID_ARGUMENT);
}

TEST(InitCleanUpFailureTests, InitFalure3Test)
{
    DEVICE_LIST_ITEM deviceList[] = 
    {
        DEVICE_LIST_ITEM(0, NULL)
    };
    ASSERT_TRUE(AmdSpl::InitializeSPL(deviceList, 0) == SPL_RESULT_INVALID_ARGUMENT);
}