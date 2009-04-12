#include "CommonTestDefs.h"
#include "RuntimeTestFixture.h"


using namespace amdspl;
using namespace amdspl::core::cal;

typedef RuntimeTestFixture BufferManagerTests;

TEST_F(BufferManagerTests, GetBufferManagerTest)
{
    ASSERT_TRUE(BufferManagerTests::_runtime->getBufferManager());
}

TEST_F(BufferManagerTests, BufferManagerCreate1DLocalBufferTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        BufferManagerTests::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_4, 1024);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}

TEST_F(BufferManagerTests, Create2DLocalBuffer1Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        BufferManagerTests::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_2, 1024, 1);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}


TEST_F(BufferManagerTests, Create2DLocalBuffer2Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        BufferManagerTests::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_1, 1024, 512);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}

TEST_F(BufferManagerTests, Create2DLocalBuffer3Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        BufferManagerTests::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_1, 8192, 8192);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}



TEST_F(BufferManagerTests, Create1DRemoteBufferTest)
{
    Buffer *buf = 
        BufferManagerTests::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_4, 1024);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}

TEST_F(BufferManagerTests, Create2DRemoteBuffer1Test)
{
    Buffer *buf = 
        BufferManagerTests::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_2, 1024, 2);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}


TEST_F(BufferManagerTests, Create2DRemoteBuffer2Test)
{
    Buffer *buf = 
        BufferManagerTests::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_1, 1024, 512);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}

TEST_F(BufferManagerTests, Create1DGlobalBufferTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        BufferManagerTests::_bufMgr->createGlobalBuffer(device, CAL_FORMAT_FLOAT_4, 1024);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}

TEST_F(BufferManagerTests, Create2DGlobalBuffer1Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        BufferManagerTests::_bufMgr->createGlobalBuffer(device, CAL_FORMAT_FLOAT_1, 1024, 1);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}


TEST_F(BufferManagerTests, Create2DGlobalBuffer2Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        BufferManagerTests::_bufMgr->createGlobalBuffer(device, CAL_FORMAT_INT_1, 1024, 512);

    ASSERT_TRUE(buf != NULL);
    _bufMgr->destroyBuffer(buf);
}


TEST_F(BufferManagerTests, GetConstBufferTest1)
{
    ConstBuffer *buf = _bufMgr->getConstBuffer(16);
    ASSERT_TRUE(buf != NULL);
    _bufMgr->releaseConstBuffer(buf);
}

TEST_F(BufferManagerTests, GetConstBufferTest2)
{
    ConstBuffer *buf1 = _bufMgr->getConstBuffer(16);
    ConstBuffer *buf2 = _bufMgr->getConstBuffer(32);
    ASSERT_TRUE(buf2 != NULL);
    _bufMgr->releaseConstBuffer(buf2);
    ConstBuffer *buf3 = _bufMgr->getConstBuffer(64);
    ASSERT_TRUE(buf1 != NULL);
    
    ASSERT_TRUE(buf3 != NULL);
    _bufMgr->releaseConstBuffer(buf1);
    _bufMgr->releaseConstBuffer(buf3);
}
