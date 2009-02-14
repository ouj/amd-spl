#include "gtest\gtest.h"
#include "amdspl.h"
#include "Runtime.h"
#include "DeviceManager.h"
#include "RuntimeTestFixture.h"
#include "BufferManager.h"
#include "ProgramManager.h"
#include "ConstBufferPool.h"

using namespace amdspl;
using namespace amdspl::core::cal;

TEST(DeviceManagerTests, RuntimeSysDeviceNumTest)
{
    DeviceManager* _deviceMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(_deviceMgr != NULL);

    CALuint deviceNum;
    calDeviceGetCount(&deviceNum);
    ASSERT_EQ(deviceNum, _deviceMgr->getSysDeviceNum());

    Runtime::destroy();
}

TEST(DeviceManagerTests, RuntimeAddDevice1Test)
{
    DeviceManager* _deviceMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(_deviceMgr != NULL);
    for (int i = 0; i < _deviceMgr->getSysDeviceNum(); i++)
    {
        ASSERT_TRUE(_deviceMgr->addDevice(i, NULL));
    }
    Runtime::destroy();
}

TEST(DeviceManagerTests, RuntimeAddDevice2Test)
{
    calInit();
    CALdevice deviceHandle;
    ASSERT_TRUE(CAL_RESULT_OK == calDeviceOpen(&deviceHandle, 0));

    DeviceManager* _deviceMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(_deviceMgr != NULL);
    ASSERT_TRUE(_deviceMgr->addDevice(0, deviceHandle));
    Runtime::destroy();

    ASSERT_TRUE(CAL_RESULT_OK == calDeviceClose(deviceHandle));
    calShutdown();
}