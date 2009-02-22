#include "CommonDefs.h"
#include "RuntimeTestFixture.h"


using namespace amdspl;
using namespace amdspl::core::cal;

typedef RuntimeTestFixture BufferManagerFailureTests;

TEST_F(BufferManagerFailureTests, CreateLocalBufferFailure1Test)
{
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(NULL, CAL_FORMAT_FLOAT_4, 1024);

    ASSERT_TRUE(buf == NULL);
}

//TEST_F(BufferManagerFailureTests, CreateLocalBufferFailure2Test)
//{
//    Device* device = _deviceMgr->getDefaultDevice();
//    ASSERT_TRUE(device);
//    Buffer *buf = 
//        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, (CALformat)-1, 1024);
//    ASSERT_TRUE(buf == NULL);
//}

TEST_F(BufferManagerFailureTests, CreateLocalBufferFailure3Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_2, -1);
    ASSERT_TRUE(buf == NULL);
}

TEST_F(BufferManagerFailureTests, CreateLocalBufferFailure4Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_4, 1024, -1);
    ASSERT_TRUE(buf == NULL);
}


//TEST_F(BufferManagerFailureTests, CreateRemoteBufferFailure2Test)
//{
//    Device* device = _deviceMgr->getDefaultDevice();
//    ASSERT_TRUE(device);
//    Buffer *buf = 
//        RuntimeTestFixture::_bufMgr->createRemoteBuffer((CALformat)-1, 1024);
//    ASSERT_TRUE(buf == NULL);
//}

TEST_F(BufferManagerFailureTests, CreateRemoteBufferFailure3Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_2, -1);
    ASSERT_TRUE(buf == NULL);
}

TEST_F(BufferManagerFailureTests, CreateRemoteBufferFailure4Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_4, 1024, -1);
    ASSERT_TRUE(buf == NULL);
}

TEST_F(BufferManagerFailureTests, CreateGlobalBufferFailure1Test)
{
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createGlobalBuffer(NULL, CAL_FORMAT_FLOAT_4, 1024);

    ASSERT_TRUE(buf == NULL);
}

//TEST_F(BufferManagerFailureTests, CreateGlobalBufferFailure2Test)
//{
//    Device* device = _deviceMgr->getDefaultDevice();
//    ASSERT_TRUE(device);
//    Buffer *buf = 
//        RuntimeTestFixture::_bufMgr->createGlobalBuffer(device, (CALformat)-1, 1024);
//    ASSERT_TRUE(buf == NULL);
//}

TEST_F(BufferManagerFailureTests, CreateGlobalBufferFailure3Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createGlobalBuffer(device, CAL_FORMAT_FLOAT_2, -1);
    ASSERT_TRUE(buf == NULL);
}

TEST_F(BufferManagerFailureTests, CreateGlobalBufferFailure4Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createGlobalBuffer(device, CAL_FORMAT_FLOAT_4, 1024, -1);
    ASSERT_TRUE(buf == NULL);
}
