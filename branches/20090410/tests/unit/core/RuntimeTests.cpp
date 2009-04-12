#include "CommonTestDefs.h"
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

TEST_F(RuntimeTestFixture, RuntimeGetBufferManagerTest)
{
    BufferManager* _deviceMgr = _runtime->getBufferManager();
    ASSERT_TRUE(_deviceMgr != NULL);
}

TEST_F(RuntimeTestFixture, RuntimeGetProgramManagerTest)
{
    ProgramManager* _deviceMgr = _runtime->getProgramManager();
    ASSERT_TRUE(_deviceMgr != NULL);
}
