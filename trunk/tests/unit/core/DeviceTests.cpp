#include "CommonDefs.h"

using namespace amdspl;
using namespace amdspl::core::cal;

TEST(DeviceTests, DeviceInit1Test)
{
    calInit();
    Device *pDevice = new Device(0, NULL);
    ASSERT_TRUE(pDevice->initialize());
    delete pDevice;
    calShutdown();
}

TEST(DeviceTests, DeviceInit2Test)
{
    calInit();
    CALdevice deviceHandle;
    ASSERT_EQ(CAL_RESULT_OK, calDeviceOpen(&deviceHandle, 0));

    Device *pDevice = new Device(0, deviceHandle);
    ASSERT_TRUE(pDevice->initialize());
    delete pDevice;

    ASSERT_EQ(CAL_RESULT_OK, calDeviceClose(deviceHandle));
    calShutdown();
}

TEST(DeviceTests, DeviceInit3Test)
{
    calInit();
    Device *pDevice = new Device(0);
    ASSERT_TRUE(pDevice->initialize());
    delete pDevice;
    calShutdown();
}

TEST(DeviceTests, DeviceGetIDTest)
{
    calInit();
    Device *pDevice = new Device(0);
    ASSERT_TRUE(pDevice->initialize());

    ASSERT_EQ(0, pDevice->getId());

    delete pDevice;
    calShutdown();
}


TEST(DeviceTests, DeviceGetInfoAndAttribsTest)
{
    calInit();
    Device *pDevice = new Device(0);
    ASSERT_TRUE(pDevice->initialize());
    CALdeviceinfo info = pDevice->getInfo();
    CALdeviceattribs attribs = pDevice->getAttribs();
    delete pDevice;
    calShutdown();
}

TEST(DeviceTests, DeviceGetContextTest)
{
    calInit();
    Device *pDevice = new Device(0);
    ASSERT_TRUE(pDevice->initialize());

    ASSERT_TRUE(pDevice->getContext() != NULL);

    delete pDevice;
    calShutdown();
}

TEST(DeviceTests, DeviceGetHandle1Test)
{
    calInit();
    Device *pDevice = new Device(0, NULL);
    ASSERT_TRUE(pDevice->initialize());

    ASSERT_TRUE(pDevice->getHandle() != NULL);

    delete pDevice;
    calShutdown();
}

TEST(DeviceTests, DeviceGetHandle2Test)
{
    calInit();
    CALdevice deviceHandle;
    ASSERT_EQ(CAL_RESULT_OK, calDeviceOpen(&deviceHandle, 0));

    Device *pDevice = new Device(0, deviceHandle);
    ASSERT_TRUE(pDevice->initialize());

    ASSERT_TRUE(pDevice->getHandle() == deviceHandle);

    delete pDevice;

    ASSERT_EQ(CAL_RESULT_OK, calDeviceClose(deviceHandle));
    calShutdown();
}
