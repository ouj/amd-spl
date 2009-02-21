#include "CommonDefs.h"
#include "RuntimeTestFixture.h"
#include "util.h"

using namespace amdspl;
using namespace amdspl::core::cal;

TEST_F(RuntimeTestFixture, LocalBufferTypeCastTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_4, 1024);

    LocalBuffer *localBuf = 
        dynamic_cast<LocalBuffer*>(buf);
    ASSERT_TRUE(localBuf != NULL);

    _bufMgr->destroyBuffer(localBuf);
}

TEST_F(RuntimeTestFixture, LocalBufferGetPropertiesTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_2, 1024);
    if (buf1D)
    {
        ASSERT_TRUE(buf1D->getResHandle() != 0);
        ASSERT_TRUE(buf1D->getFormat() == CAL_FORMAT_FLOAT_2);
        ASSERT_TRUE(buf1D->getWidth() == 1024);
        ASSERT_TRUE(buf1D->getHeight() == 0);
    }
    _bufMgr->destroyBuffer(buf1D);

    Buffer *buf2D = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_INT_1, 1024, 1024);
    if (buf2D)
    {
        ASSERT_TRUE(buf2D->getResHandle() != 0);
        ASSERT_TRUE(buf2D->getFormat() == CAL_FORMAT_INT_1);
        ASSERT_TRUE(buf2D->getWidth() == 1024);
        ASSERT_TRUE(buf2D->getHeight() == 1024);
    }
    _bufMgr->destroyBuffer(buf2D);
}

TEST_F(RuntimeTestFixture, LocalBufferReadWriteData1Test)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_2, 1024);

    if (buf1D)
    {
        ASSERT_TRUE(buf1D->getResHandle() != 0);
        ASSERT_TRUE(buf1D->getFormat() == CAL_FORMAT_FLOAT_2);
        ASSERT_TRUE(buf1D->getWidth() == 1024);
        ASSERT_TRUE(buf1D->getHeight() == 0);
    }
    vector<float2> cpuBuf;
    util::initializeBuffer(cpuBuf, 1024, 0, 1000, util::RANDOM);

    ASSERT_TRUE(buf1D->readData(&cpuBuf[0], cpuBuf.size()));
    vector<float2> result;
    result.resize(1024);
    ASSERT_TRUE(buf1D->writeData(&result[0], result.size()));

    ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, cpuBuf.size()));

    _bufMgr->destroyBuffer(buf1D);
}

TEST_F(RuntimeTestFixture, LocalBufferReadWriteData2Test)
{
    unsigned int width = 78;
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_INT_2, width, 0);

    if (buf)
    {
        ASSERT_TRUE(buf->getResHandle() != 0);
        ASSERT_TRUE(buf->getFormat() == CAL_FORMAT_INT_2);
        ASSERT_TRUE(buf->getWidth() == width);
        ASSERT_TRUE(buf->getHeight() == 0);
    }
    vector<int2> cpuBuf;
    util::initializeBuffer(cpuBuf, width, 1, 1000, util::RANDOM);

    ASSERT_TRUE(buf->readData(&cpuBuf[0], cpuBuf.size()));
    vector<int2> result;
    result.resize(width);
    ASSERT_TRUE(buf->writeData(&result[0], result.size()));

    ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, cpuBuf.size()));

    _bufMgr->destroyBuffer(buf);
}

TEST_F(RuntimeTestFixture, LocalBufferReadWriteData3Test)
{
    unsigned int width = 888;
    unsigned int height = 999;
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_DOUBLE_2, width, height);

    if (buf1D)
    {
        ASSERT_TRUE(buf1D->getResHandle() != 0);
        ASSERT_TRUE(buf1D->getFormat() == CAL_FORMAT_DOUBLE_2);
        ASSERT_TRUE(buf1D->getWidth() == width);
        ASSERT_TRUE(buf1D->getHeight() == height);
    }
    vector<double2> cpuBuf;
    util::initializeBuffer(cpuBuf, width, height, 1000, util::RANDOM);

    ASSERT_TRUE(buf1D->readData(&cpuBuf[0], cpuBuf.size()));
    vector<double2> result;
    result.resize(width * height);
    ASSERT_TRUE(buf1D->writeData(&result[0], result.size()));

    ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, cpuBuf.size()));

    _bufMgr->destroyBuffer(buf1D);
}