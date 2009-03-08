#include "cal.h"
#include "amdspl.h"
#include "BitonicSortTest.h"

using namespace amdspl;
using namespace amdspl::core::cal;

bool BitonicSortTest::m_Fatal = false;
unsigned int BitonicSortTest::Length;

// A problem that can be handled.
#define TEST_LOG_CAL_RESULT(result, msg) \
    if ((result) != CAL_RESULT_OK) \
{ \
    SCOPED_TRACE(msg);\
    return; \
}

void BitonicSortTest::SetUpTestCase()
{
    ASSERT_TRUE(Runtime::getInstance());
    DeviceManager *devMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(devMgr);

    unsigned int sysDevNum = devMgr->getSysDeviceNum();

    for (unsigned int i = 0; i < sysDevNum; i++)
    {
        ASSERT_TRUE(devMgr->assignDevice(i));
    }

    CALdeviceinfo info = devMgr->getDefaultDevice()->getInfo();

    Length = info.maxResource2DWidth * 
        info.maxResource2DHeight;

}

bool BitonicSortTest::HasFatalFailure()
{
    return m_Fatal;
}

void BitonicSortTest::TearDownTestCase()
{
    Runtime::destroy();
}
