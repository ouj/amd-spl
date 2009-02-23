#include "RuntimeTestFixture.h"
#include "amdspl.h"

using namespace amdspl;

Runtime* RuntimeTestFixture::_runtime = NULL;
BufferManager* RuntimeTestFixture::_bufMgr = NULL;
DeviceManager* RuntimeTestFixture::_deviceMgr = NULL;
ProgramManager* RuntimeTestFixture::_progMgr = NULL;

RuntimeTestFixture::RuntimeTestFixture(void)
{
}

RuntimeTestFixture::~RuntimeTestFixture(void)
{
}

void RuntimeTestFixture::SetUpTestCase()
{
    DEVICE_LIST_ITEM deviceList[] = 
    {
        DEVICE_LIST_ITEM(0, 0)
    };
    ASSERT_EQ(SPL_RESULT_OK, AmdSpl::InitializeSPL(deviceList, 1, 0));

}

void RuntimeTestFixture::TearDownTestCase()
{
    ASSERT_EQ(SPL_RESULT_OK, AmdSpl::CleanupSPL());
}

void RuntimeTestFixture::SetUp()
{
    _runtime = Runtime::getInstance();
    _bufMgr = _runtime->getBufferManager();
    _deviceMgr = _runtime->getDeviceManager();
    _progMgr = _runtime->getProgramManager();
}

void RuntimeTestFixture::TearDown()
{
    _runtime = NULL;
    _bufMgr = NULL;
    _deviceMgr = NULL;
    _progMgr = NULL;
}