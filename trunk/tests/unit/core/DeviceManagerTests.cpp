#include "CommonTestDefs.h"

using namespace amdspl;
using namespace amdspl::core::cal;

TEST(DeviceManagerTests, RuntimeSysDeviceNumTest)
{
    DeviceManager* _deviceMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(_deviceMgr != NULL);

    CALuint deviceNum;
    calDeviceGetCount(&deviceNum);
    ASSERT_EQ(deviceNum, _deviceMgr->getSysDeviceNum());

    printf_s("System Device Number: %d\n", _deviceMgr->getSysDeviceNum());

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
    ASSERT_EQ(CAL_RESULT_OK, calDeviceOpen(&deviceHandle, 0));

    DeviceManager* _deviceMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(_deviceMgr != NULL);
    ASSERT_TRUE(_deviceMgr->addDevice(0, deviceHandle));
    Runtime::destroy();

    ASSERT_EQ(CAL_RESULT_OK, calDeviceClose(deviceHandle));
    calShutdown();
}

TEST(DeviceManagerTests, GetDeviceNumTest)
{
    DeviceManager* _deviceMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(_deviceMgr != NULL);

    ASSERT_TRUE(_deviceMgr->addDevice(0, NULL));

    ASSERT_EQ(1, _deviceMgr->getDeviceNum());
    Runtime::destroy();
}

TEST(DeviceManagerTests, GetDeviceByIDTest)
{
    DeviceManager* _deviceMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(_deviceMgr != NULL);
    for (int i = 0; i < _deviceMgr->getSysDeviceNum(); i++)
    {
        ASSERT_TRUE(_deviceMgr->addDevice(i, NULL));
    }

    Device *pDevice = _deviceMgr->getDeviceByID(0);
    ASSERT_TRUE(pDevice != NULL);

    ASSERT_EQ(0, pDevice->getId());
    Runtime::destroy();
}

TEST(DeviceManagerTests, SetGetDefualtDeviceTest)
{
    DeviceManager* _deviceMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(_deviceMgr != NULL);
    for (int i = 0; i < _deviceMgr->getSysDeviceNum(); i++)
    {
        ASSERT_TRUE(_deviceMgr->addDevice(i, NULL));
    }

    ASSERT_TRUE(_deviceMgr->setDefaultDevice(0));

    Device *pDevice = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(pDevice != NULL);
    ASSERT_EQ(0, pDevice->getId());
    Runtime::destroy();
}