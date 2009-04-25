#include "CommonTestDefs.h"
#include "RuntimeTestFixture.h"
#include "util.h"
#include <time.h>
#include "Perf.h"

using namespace amdspl;
using namespace amdspl::core::cal;

typedef RuntimeTestFixture AsyncDataTransferTests;

TEST_F(AsyncDataTransferTests, LocalMemoryDMAReadWriteTest)
{
    CPerfCounter timer;

    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    CALdeviceinfo info = device->getInfo();

    Buffer *buf1D = 
        _bufMgr->createLocalBuffer(device, CAL_FORMAT_INT_1, info.maxResource2DWidth, info.maxResource2DHeight, 0);

    printf("Data size %d * %d:\n", info.maxResource2DWidth, info.maxResource2DHeight);
    if (buf1D)
    {
        vector<int> cpuBuf(info.maxResource2DWidth * info.maxResource2DHeight);
        vector<int> result(cpuBuf.size());
        util::initializeBuffer(cpuBuf, info.maxResource2DWidth, 
            info.maxResource2DHeight, 0x10000, util::RANDOM);

        timer.Reset();
        timer.Start();
        ASSERT_TRUE(buf1D->readData(&cpuBuf[0], static_cast<unsigned long>(cpuBuf.size())));
        ASSERT_TRUE(buf1D->writeData(&result[0], static_cast<unsigned long>(result.size())));
        timer.Stop();
        printf("ASync Copy Time: %.10lf\t", timer.GetElapsedTime());
        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, static_cast<unsigned long>(cpuBuf.size())));

        timer.Reset();
        timer.Start();
        ASSERT_TRUE(buf1D->Buffer::readData(&cpuBuf[0], static_cast<unsigned long>(cpuBuf.size())));
        ASSERT_TRUE(buf1D->Buffer::writeData(&result[0], static_cast<unsigned long>(result.size())));
        timer.Stop();
        printf("Sync Copy Time: %.10lf\n", timer.GetElapsedTime());
        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, static_cast<unsigned long>(cpuBuf.size())));

        _bufMgr->destroyBuffer(buf1D);
    }
    else
        FAIL();
}