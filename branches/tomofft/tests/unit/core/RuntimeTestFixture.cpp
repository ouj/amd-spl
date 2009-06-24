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
    ASSERT_TRUE(Runtime::getInstance());
    DeviceManager *devMgr = Runtime::getInstance()->getDeviceManager();
    ASSERT_TRUE(devMgr);

    unsigned int sysDevNum = devMgr->getSysDeviceNum();

    for (unsigned int i = 0; i < sysDevNum; i++)
    {
        ASSERT_TRUE(devMgr->assignDevice(i));
    }
}

void RuntimeTestFixture::TearDownTestCase()
{
    Runtime::destroy();
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
