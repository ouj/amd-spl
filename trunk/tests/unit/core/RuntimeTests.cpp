#include "gtest\gtest.h"
#include "amdspl.h"
#include "Runtime.h"
#include "DeviceManager.h"
#include "RuntimeTestFixture.h"

using namespace amdspl;
using namespace amdspl::core::cal;

TEST(RuntimeTests, RuntimeGetInstanceTest)
{
    ASSERT_TRUE(Runtime::getInstance() != NULL);
}

TEST_F(RuntimeTestFixture, RuntimeGetDeviceManagerTest)
{
    DeviceManager* _deviceMgr = _runtime->getDeviceManager();
    ASSERT_TRUE(_deviceMgr != NULL);
}
