#include "CommonTestDefs.h"
#include "RuntimeTestFixture.h"
#include "util.h"

using namespace amdspl;
using namespace amdspl::core::cal;

typedef RuntimeTestFixture BufferStressTests;

TEST_F(BufferStressTests, BufferReadWriteStressTest1)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    CALdeviceinfo info = device->getInfo();
    info.maxResource2DHeight = 2048;

    //util::printDeviceStatus(device);
    Buffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_4, info.maxResource2DWidth, info.maxResource2DHeight);
    //util::printDeviceStatus(device);

    if (buf1D)
    {
        vector<float4> cpuBuf(info.maxResource2DWidth * info.maxResource2DHeight);
        util::initializeBuffer(cpuBuf, info.maxResource2DWidth, info.maxResource2DHeight, 1000, util::RANDOM);

        ASSERT_TRUE(buf1D->readData(&cpuBuf[0], cpuBuf.size()));
        vector<float4> result;
        result.resize(info.maxResource2DWidth * info.maxResource2DHeight);
        ASSERT_TRUE(buf1D->writeData(&result[0], result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, cpuBuf.size()));

        _bufMgr->destroyBuffer(buf1D);
    }
    else
        FAIL();
}