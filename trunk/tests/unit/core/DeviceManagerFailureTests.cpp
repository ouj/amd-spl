#include "CommonTestDefs.h"

using namespace amdspl;
using namespace amdspl::core::cal;

TEST(DeviceManagerFailureTests, RuntimeAddDeviceFailure1Test)
{
    DeviceManager* _deviceMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(_deviceMgr != NULL);
    ASSERT_FALSE(_deviceMgr->addDevice(-1, NULL));
    Runtime::destroy();
}

TEST(DeviceManagerFailureTests, RuntimeAddDeviceFailure2Test)
{
    DeviceManager* _deviceMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(_deviceMgr != NULL);
    ASSERT_FALSE(_deviceMgr->addDevice(0, 0xEFEFEFEF));
    Runtime::destroy();
}

TEST(DeviceManagerFailureTests, GetDeviceByIDFailureTest)
{
    DeviceManager* _deviceMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(_deviceMgr != NULL);
    for (int i = 0; i < _deviceMgr->getSysDeviceNum(); i++)
    {
        ASSERT_TRUE(_deviceMgr->addDevice(i, NULL));
    }

    Device *pDevice = _deviceMgr->getDeviceByID(-1);
    ASSERT_TRUE(pDevice == NULL);
    Runtime::destroy();
}

TEST(DeviceManagerFailureTests, SetDeviceFailureTest)
{
    DeviceManager* _deviceMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(_deviceMgr != NULL);
    for (int i = 0; i < _deviceMgr->getSysDeviceNum(); i++)
    {
        ASSERT_TRUE(_deviceMgr->addDevice(i, NULL));
    }

    ASSERT_FALSE(_deviceMgr->setDefaultDevice(-1));

    Device *pDevice = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(pDevice != NULL);

    Runtime::destroy();
}