#include "CommonDefs.h"
#include "RuntimeTestFixture.h"


using namespace amdspl;
using namespace amdspl::core::cal;

TEST_F(RuntimeTestFixture, GetBufferManagerTest)
{
    ASSERT_TRUE(RuntimeTestFixture::_runtime->getBufferManager());
}

TEST_F(RuntimeTestFixture, BufferManagerCreate1DLocalBufferTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_4, 1024);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}

TEST_F(RuntimeTestFixture, BufferManagerCreate2DLocalBuffer1Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_2, 1024, 1);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}


TEST_F(RuntimeTestFixture, BufferManagerCreate2DLocalBuffer2Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_1, 1024, 512);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}

TEST_F(RuntimeTestFixture, BufferManagerCreate2DLocalBuffer3Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_1, 8192, 8192);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}



TEST_F(RuntimeTestFixture, BufferManagerCreate1DRemoteBufferTest)
{
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_4, 1024);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}

TEST_F(RuntimeTestFixture, BufferManagerCreate2DRemoteBuffer1Test)
{
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_2, 1024, 2);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}


TEST_F(RuntimeTestFixture, BufferManagerCreate2DRemoteBuffer2Test)
{
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_1, 1024, 512);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}

TEST_F(RuntimeTestFixture, BufferManagerCreate1DGlobalBufferTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createGlobalBuffer(device, CAL_FORMAT_FLOAT_4, 1024);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}

TEST_F(RuntimeTestFixture, BufferManagerCreate2DGlobalBuffer1Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createGlobalBuffer(device, CAL_FORMAT_FLOAT_1, 1024, 1);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}


TEST_F(RuntimeTestFixture, BufferManagerCreate2DGlobalBuffer2Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createGlobalBuffer(device, CAL_FORMAT_INT_1, 1024, 512);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}
