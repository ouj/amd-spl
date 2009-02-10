#include "RuntimeTestFixture.h"
#include "amdspl.h"

using namespace amdspl;

Runtime* RuntimeTestFixture::_runtime = NULL;

RuntimeTestFixture::RuntimeTestFixture(void)
{
}

RuntimeTestFixture::~RuntimeTestFixture(void)
{
}

void RuntimeTestFixture::SetUpTestCase()
{
    _runtime = Runtime::getInstance();
}

void RuntimeTestFixture::TearDownTestCase()
{
    _runtime = NULL;
}

void RuntimeTestFixture::SetUp()
{
    DEVICE_LIST_ITEM deviceList[] = 
    {
        DEVICE_LIST_ITEM(0, 0)
    };
    ASSERT_TRUE(AmdSpl::InitializeSPL(deviceList, 1, 0) == SPL_RESULT_OK);
}

void RuntimeTestFixture::TearDown()
{
    ASSERT_TRUE(AmdSpl::CleanupSPL() == SPL_RESULT_OK);
}