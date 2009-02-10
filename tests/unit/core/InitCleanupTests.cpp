#include "gtest\gtest.h"
#include "amdspl.h"
#include "Runtime.h"

using namespace amdspl;
using namespace amdspl::core::cal;

TEST(InitCleanUpTests, InitCleanUpTest)
{
    DEVICE_LIST_ITEM deviceList[] = 
    {
        DEVICE_LIST_ITEM(0, NULL)
    };
    ASSERT_TRUE(AmdSpl::InitializeSPL(deviceList, 1, 0) == SPL_RESULT_OK);
    ASSERT_TRUE(Runtime::getInstance() != NULL);
    ASSERT_TRUE(AmdSpl::CleanupSPL() == SPL_RESULT_OK);
}
