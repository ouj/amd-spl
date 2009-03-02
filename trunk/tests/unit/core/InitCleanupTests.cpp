#include "gtest\gtest.h"
#include "amdspl.h"
#include "Runtime.h"

using namespace amdspl;
using namespace amdspl::core::cal;

TEST(InitCleanUpTests, InitCleanUpTest)
{
    ASSERT_TRUE(Runtime::getInstance() != NULL);
    Runtime::destroy();
}
