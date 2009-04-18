#include "CommonTestDefs.h"
#include "RuntimeTestFixture.h"
#include "util.h"

using namespace amdspl;
using namespace amdspl::core::cal;

typedef RuntimeTestFixture GlobalBufferTests;

TEST_F(GlobalBufferTests, GlobalBufferTypeCastTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_4, 1024, 0, CAL_RESALLOC_GLOBAL_BUFFER);

    ASSERT_TRUE(buf != NULL);

    _bufMgr->destroyBuffer(buf);
}

TEST_F(GlobalBufferTests, GlobalBufferGetPropertiesTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_2, 1024, 0, CAL_RESALLOC_GLOBAL_BUFFER);
    if (buf1D)
    {
        ASSERT_TRUE(buf1D->getResHandle() != 0);
        ASSERT_TRUE(buf1D->getFormat() == CAL_FORMAT_FLOAT_2);
        ASSERT_TRUE(buf1D->getWidth() == 1024);
        ASSERT_TRUE(buf1D->getHeight() == 0);
    }
    _bufMgr->destroyBuffer(buf1D);

    Buffer *buf2D = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_INT_1, 1024, 1024, CAL_RESALLOC_GLOBAL_BUFFER);
    if (buf2D)
    {
        ASSERT_TRUE(buf2D->getResHandle() != 0);
        ASSERT_TRUE(buf2D->getFormat() == CAL_FORMAT_INT_1);
        ASSERT_TRUE(buf2D->getWidth() == 1024);
        ASSERT_TRUE(buf2D->getHeight() == 1024);
    }
    _bufMgr->destroyBuffer(buf2D);
}

TEST_F(GlobalBufferTests, GlobalBufferReadWriteData1Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_2, 1024, 0, CAL_RESALLOC_GLOBAL_BUFFER);

    if (buf1D)
    {
        vector<float2> cpuBuf(1024);
        util::initializeBuffer(cpuBuf, 1024, 0, 1000, util::RANDOM);

        ASSERT_TRUE(buf1D->readData(&cpuBuf[0], (unsigned long)cpuBuf.size()));
        vector<float2> result;
        result.resize(1024);
        ASSERT_TRUE(buf1D->writeData(&result[0], (unsigned long)result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, (unsigned long)cpuBuf.size()));

        _bufMgr->destroyBuffer(buf1D);
    }
    else
        FAIL();
}

TEST_F(GlobalBufferTests, GlobalBufferReadWriteData2Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_INT_2, 78, 0, CAL_RESALLOC_GLOBAL_BUFFER);

    if (buf)
    {
        vector<int2> cpuBuf(78);
        util::initializeBuffer(cpuBuf, 78, 1, 1000, util::RANDOM);

        ASSERT_TRUE(buf->readData(&cpuBuf[0], (unsigned long)cpuBuf.size()));
        vector<int2> result;
        result.resize(78);
        ASSERT_TRUE(buf->writeData(&result[0], (unsigned long)result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, (unsigned long)cpuBuf.size()));

        _bufMgr->destroyBuffer(buf);
    }
    else
        FAIL();
}

TEST_F(GlobalBufferTests, GlobalBufferReadWriteData3Test)
{
    unsigned int width = 512;
    unsigned int height = 999;
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_DOUBLE_2, width, height, CAL_RESALLOC_GLOBAL_BUFFER);

    if (buf1D)
    {
        vector<double2> cpuBuf(width * height);
        util::initializeBuffer(cpuBuf, width, height, 1000, util::RANDOM);

        ASSERT_TRUE(buf1D->readData(&cpuBuf[0], (unsigned long)cpuBuf.size()));
        vector<double2> result;
        result.resize(width * height);
        ASSERT_TRUE(buf1D->writeData(&result[0], (unsigned long)result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, (unsigned long)cpuBuf.size()));

        _bufMgr->destroyBuffer(buf1D);
    }
    else
        FAIL();
}


TEST_F(GlobalBufferTests, GlobalBufferReadWriteData5Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_INT_1, 1024, 1024, CAL_RESALLOC_GLOBAL_BUFFER);

    if (buf1D)
    {
        vector<int> cpuBuf(1024 * 1024, 123321);
        util::initializeBuffer(cpuBuf, 120, 10, 1000, util::RANDOM);

        int defaultVal = 123321;
        ASSERT_TRUE(buf1D->readData(&cpuBuf[0], 1200, &defaultVal));
        vector<int> result(1024 * 1024);
        ASSERT_TRUE(buf1D->writeData(&result[0], (unsigned long)result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, (unsigned long)cpuBuf.size()));

        _bufMgr->destroyBuffer(buf1D);
    }
    else
        FAIL();
}

TEST_F(GlobalBufferTests, GlobalRemoteBufferTypeCastTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_4, 1024, 0, CAL_RESALLOC_GLOBAL_BUFFER);

    ASSERT_TRUE(buf != NULL);

    _bufMgr->destroyBuffer(buf);
}

TEST_F(GlobalBufferTests, GlobalRemoteBufferGetPropertiesTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_2, 1024, 0, CAL_RESALLOC_GLOBAL_BUFFER);
    if (buf1D)
    {
        ASSERT_TRUE(buf1D->getResHandle() != 0);
        ASSERT_TRUE(buf1D->getFormat() == CAL_FORMAT_FLOAT_2);
        ASSERT_TRUE(buf1D->getWidth() == 1024);
        ASSERT_TRUE(buf1D->getHeight() == 0);
    }
    _bufMgr->destroyBuffer(buf1D);

    Buffer *buf2D = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_INT_1, 1024, 1024, CAL_RESALLOC_GLOBAL_BUFFER);
    if (buf2D)
    {
        ASSERT_TRUE(buf2D->getResHandle() != 0);
        ASSERT_TRUE(buf2D->getFormat() == CAL_FORMAT_INT_1);
        ASSERT_TRUE(buf2D->getWidth() == 1024);
        ASSERT_TRUE(buf2D->getHeight() == 1024);
    }
    _bufMgr->destroyBuffer(buf2D);
}

TEST_F(GlobalBufferTests, GlobalRemoteBufferReadWriteData1Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_FLOAT_2, 1024, 0, CAL_RESALLOC_GLOBAL_BUFFER);

    if (buf1D)
    {
        vector<float2> cpuBuf(1024);
        util::initializeBuffer(cpuBuf, 1024, 0, 1000, util::RANDOM);

        ASSERT_TRUE(buf1D->readData(&cpuBuf[0], (unsigned long)cpuBuf.size()));
        vector<float2> result;
        result.resize(1024);
        ASSERT_TRUE(buf1D->writeData(&result[0], (unsigned long)result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, (unsigned long)cpuBuf.size()));

        _bufMgr->destroyBuffer(buf1D);
    }
    else
        FAIL();
}

TEST_F(GlobalBufferTests, GlobalRemoteBufferReadWriteData2Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_INT_2, 78, 0, CAL_RESALLOC_GLOBAL_BUFFER);

    if (buf)
    {
        vector<int2> cpuBuf(78);
        util::initializeBuffer(cpuBuf, 78, 1, 1000, util::RANDOM);

        ASSERT_TRUE(buf->readData(&cpuBuf[0], (unsigned long)cpuBuf.size()));
        vector<int2> result;
        result.resize(78);
        ASSERT_TRUE(buf->writeData(&result[0], (unsigned long)result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, (unsigned long)cpuBuf.size()));

        _bufMgr->destroyBuffer(buf);
    }
    else
        FAIL();
}

TEST_F(GlobalBufferTests, GlobalRemoteBufferReadWriteData3Test)
{
    unsigned int width = 512;
    unsigned int height = 999;
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_DOUBLE_2, width, height, CAL_RESALLOC_GLOBAL_BUFFER);

    if (buf1D)
    {
        vector<double2> cpuBuf(width * height);
        util::initializeBuffer(cpuBuf, width, height, 1000, util::RANDOM);

        ASSERT_TRUE(buf1D->readData(&cpuBuf[0], (unsigned long)cpuBuf.size()));
        vector<double2> result;
        result.resize(width * height);
        ASSERT_TRUE(buf1D->writeData(&result[0], (unsigned long)result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, (unsigned long)cpuBuf.size()));

        _bufMgr->destroyBuffer(buf1D);
    }
    else
        FAIL();
}


TEST_F(GlobalBufferTests, GlobalRemoteBufferReadWriteData5Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createRemoteBuffer(CAL_FORMAT_INT_1, 1024, 1024, CAL_RESALLOC_GLOBAL_BUFFER);

    if (buf1D)
    {
        vector<int> cpuBuf(1024 * 1024, 123321);
        util::initializeBuffer(cpuBuf, 120, 10, 1000, util::RANDOM);

        int defaultVal = 123321;
        ASSERT_TRUE(buf1D->readData(&cpuBuf[0], 1200, &defaultVal));
        vector<int> result(1024 * 1024);
        ASSERT_TRUE(buf1D->writeData(&result[0], (unsigned long)result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, (unsigned long)cpuBuf.size()));

        _bufMgr->destroyBuffer(buf1D);
    }
    else
        FAIL();
}
