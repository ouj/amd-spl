#include "cal.h"
#include "BitonicSortTest.h"



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
    CALresult result;
    result = calInit();
    if (result != CAL_RESULT_OK)
    {
        SCOPED_TRACE("Failed to initial CAL");
        m_Fatal = true;
    }
    //! \brief CALdevice info properties
    CALdeviceinfo _calDeviceInfo;

    result = calDeviceGetInfo(&_calDeviceInfo, 0);
    TEST_LOG_CAL_RESULT(result, "Failed to get info on CAL device \n");

    Length = _calDeviceInfo.maxResource2DWidth * 
        _calDeviceInfo.maxResource2DHeight;

    calShutdown();
}

bool BitonicSortTest::HasFatalFailure()
{
    return m_Fatal;
}

void BitonicSortTest::TearDownTestCase()
{
}
