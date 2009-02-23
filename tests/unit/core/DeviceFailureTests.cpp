#include "CommonTestDefs.h"

using namespace amdspl;
using namespace amdspl::core::cal;

TEST(DeviceFailureTests, DeviceInitFailure1Test)
{
    calInit();
    Device *pDevice = new Device(-1, NULL);
    ASSERT_FALSE(pDevice->initialize());
    delete pDevice;
    calShutdown();
}

TEST(DeviceFailureTests, DeviceInitFailure2Test)
{
    calInit();

    Device *pDevice = new Device(0, 0xEFEFEFEF);
    ASSERT_FALSE(pDevice->initialize());
    delete pDevice;

    calShutdown();
}