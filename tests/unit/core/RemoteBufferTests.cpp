#include "CommonDefs.h"
#include "RuntimeTestFixture.h"
#include "util.h"

using namespace amdspl;
using namespace amdspl::core::cal;

typedef RuntimeTestFixture RemoteBufferTests;

TEST_F(RemoteBufferTests, RemoteBufferTypeCastTest)
{
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_4, 1024);

    RemoteBuffer *remoteBuf = 
        dynamic_cast<RemoteBuffer*>(buf);
    ASSERT_TRUE(remoteBuf != NULL);

    _bufMgr->destroyBuffer(remoteBuf);
}

TEST_F(RemoteBufferTests, RemoteBufferGetPropertiesTest)
{
    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_2, 1024);
    if (buf1D)
    {
        ASSERT_TRUE(buf1D->getResHandle() != 0);
        ASSERT_TRUE(buf1D->getFormat() == CAL_FORMAT_FLOAT_2);
        ASSERT_TRUE(buf1D->getWidth() == 1024);
        ASSERT_TRUE(buf1D->getHeight() == 0);
    }
    _bufMgr->destroyBuffer(buf1D);

    Buffer *buf2D = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_INT_1, 1024, 1024);
    if (buf2D)
    {
        ASSERT_TRUE(buf2D->getResHandle() != 0);
        ASSERT_TRUE(buf2D->getFormat() == CAL_FORMAT_INT_1);
        ASSERT_TRUE(buf2D->getWidth() == 1024);
        ASSERT_TRUE(buf2D->getHeight() == 1024);
    }
    _bufMgr->destroyBuffer(buf2D);
}

TEST_F(RemoteBufferTests, RemoteBufferReadWriteData1Test)
{
    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_2, 1024);

    if (buf1D)
    {
        vector<float2> cpuBuf(1024);
        util::initializeBuffer(cpuBuf, 1024, 0, 1000, util::RANDOM);

        ASSERT_TRUE(buf1D->readData(&cpuBuf[0], cpuBuf.size()));
        vector<float2> result;
        result.resize(1024);
        ASSERT_TRUE(buf1D->writeData(&result[0], result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, cpuBuf.size()));

        _bufMgr->destroyBuffer(buf1D);
    }
    else
        FAIL();
}

TEST_F(RemoteBufferTests, RemoteBufferReadWriteData2Test)
{
    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_INT_2, 78, 0);

    if (buf)
    {
        vector<int2> cpuBuf(78);
        util::initializeBuffer(cpuBuf, 78, 1, 1000, util::RANDOM);

        ASSERT_TRUE(buf->readData(&cpuBuf[0], cpuBuf.size()));
        vector<int2> result;
        result.resize(78);
        ASSERT_TRUE(buf->writeData(&result[0], result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, cpuBuf.size()));

        _bufMgr->destroyBuffer(buf);
    }
    else
        FAIL();
}

TEST_F(RemoteBufferTests, RemoteBufferReadWriteData3Test)
{
    unsigned int width = 888;
    unsigned int height = 999;

    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_DOUBLE_2, width, height);

    if (buf1D)
    {
        vector<double2> cpuBuf(width * height);
        util::initializeBuffer(cpuBuf, width, height, 1000, util::RANDOM);

        ASSERT_TRUE(buf1D->readData(&cpuBuf[0], cpuBuf.size()));
        vector<double2> result;
        result.resize(width * height);
        ASSERT_TRUE(buf1D->writeData(&result[0], result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, cpuBuf.size()));

        _bufMgr->destroyBuffer(buf1D);
    }
    else
        FAIL();
}


TEST_F(RemoteBufferTests, RemoteBufferReadWriteData5Test)
{
    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_INT_1, 1024, 1024);

    if (buf1D)
    {
        vector<int> cpuBuf(1024 * 1024, 123321);
        util::initializeBuffer(cpuBuf, 120, 10, 1000, util::RANDOM);

        int defaultVal = 123321;
        ASSERT_TRUE(buf1D->readData(&cpuBuf[0], 1200, &defaultVal));
        vector<int> result(1024 * 1024);
        ASSERT_TRUE(buf1D->writeData(&result[0], result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, cpuBuf.size()));

        _bufMgr->destroyBuffer(buf1D);
    }
    else
        FAIL();
}