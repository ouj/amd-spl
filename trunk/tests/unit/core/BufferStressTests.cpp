#include "CommonTestDefs.h"
#include "RuntimeTestFixture.h"
#include "util.h"
#include "Perf.h"

using namespace amdspl;
using namespace amdspl::core::cal;

typedef RuntimeTestFixture BufferStressTests;


template<typename T>
static void BufferReadWriteStress(const vector<T> &arrayi)
{
    CPerfCounter timer;
    for (unsigned int size = 32; size <= BitonicSortTest::Length; size = size << 1)
    {
        printf("Test Size %16d\t", size);
        vector<T> vec(arrayi.begin(), arrayi.begin() + size);

        timer.Reset();
        timer.Start();
        timer.Stop();

        printf("Time: %.10lf\n", timer.GetElapsedTime());

        else
            printf("...Failed\n");
    }
}


TEST_F(BufferStressTests, BufferReadWriteStressTest1)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    CALdeviceinfo info = device->getInfo();
    info.maxResource2DHeight = 1024;

    //util::printDeviceStatus(device);
    //util::printDeviceStatus(device);


    CPerfCounter timer;
    vector<float4> cpuBuf(info.maxResource2DWidth * info.maxResource2DHeight);
    util::initializeBuffer(cpuBuf, info.maxResource2DWidth, info.maxResource2DHeight, 1000, util::RANDOM);

    for (unsigned int i = 32; i < cpuBuf.size(); i *= 2)
    {
        Buffer *buf1D = 
            i <= info.maxResource2DWidth ?
            RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_4, i, 0, 0) :
            RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_4, info.maxResource2DWidth, i / info.maxResource2DWidth, 0);
        
        if (buf1D)
        {
            timer.Reset();
            timer.Start();
            ASSERT_TRUE(buf1D->readData(&cpuBuf[0], static_cast<unsigned long>(i)));
            timer.Stop();
            printf("Read %d float4 time: %lf\n", i, timer.GetElapsedTime());


            vector<float4> result;
            result.resize(info.maxResource2DWidth * info.maxResource2DHeight);
            timer.Reset();
            timer.Start();
            ASSERT_TRUE(buf1D->writeData(&result[0], static_cast<unsigned long>(i)));
            timer.Stop();
            printf("Write %d float4 time: %lf\n", i, timer.GetElapsedTime());
            ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, static_cast<unsigned long>(i)));
        }

        _bufMgr->destroyBuffer(buf1D);
    }
}
