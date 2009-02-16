#include "CommonDefs.h"
#include "RuntimeTestFixture.h"


using namespace amdspl;
using namespace amdspl::core::cal;

TEST_F(RuntimeTestFixture, BufferManagerCreateLocalBufferFailure1Test)
{
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(NULL, CAL_FORMAT_FLOAT_4, 1024);

    ASSERT_TRUE(buf == NULL);
}

TEST_F(RuntimeTestFixture, BufferManagerCreateLocalBufferFailure2Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, (CALformat)-1, 1024);
    ASSERT_TRUE(buf == NULL);
}

TEST_F(RuntimeTestFixture, BufferManagerCreateLocalBufferFailure3Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_2, -1);
    ASSERT_TRUE(buf == NULL);
}

TEST_F(RuntimeTestFixture, BufferManagerCreateLocalBufferFailure4Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_4, 1024, -1);
    ASSERT_TRUE(buf == NULL);
}


TEST_F(RuntimeTestFixture, BufferManagerCreateRemoteBufferFailure2Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer((CALformat)-1, 1024);
    ASSERT_TRUE(buf == NULL);
}

TEST_F(RuntimeTestFixture, BufferManagerCreateRemoteBufferFailure3Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_2, -1);
    ASSERT_TRUE(buf == NULL);
}

TEST_F(RuntimeTestFixture, BufferManagerCreateRemoteBufferFailure4Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_4, 1024, -1);
    ASSERT_TRUE(buf == NULL);
}

TEST_F(RuntimeTestFixture, BufferManagerCreateScatterBufferFailure1Test)
{
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createScatterBuffer(NULL, CAL_FORMAT_FLOAT_4, 1024);

    ASSERT_TRUE(buf == NULL);
}

TEST_F(RuntimeTestFixture, BufferManagerCreateScatterBufferFailure2Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createScatterBuffer(device, (CALformat)-1, 1024);
    ASSERT_TRUE(buf == NULL);
}

TEST_F(RuntimeTestFixture, BufferManagerCreateScatterBufferFailure3Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createScatterBuffer(device, CAL_FORMAT_FLOAT_2, -1);
    ASSERT_TRUE(buf == NULL);
}

TEST_F(RuntimeTestFixture, BufferManagerCreateScatterBufferFailure4Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createScatterBuffer(device, CAL_FORMAT_FLOAT_4, 1024, -1);
    ASSERT_TRUE(buf == NULL);
}
