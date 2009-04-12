#include "CommonTestDefs.h"
#include "RuntimeTestFixture.h"
#include "util.h"

using namespace amdspl;
using namespace amdspl::core::cal;

typedef RuntimeTestFixture ILMemoryTest;

typedef ProgramInfo<0, 0, 0, true>  GlobalMemoryProgram;
static const char* _sz_global_prog_source_ = IL_KERNEL(
    il_ps_2_0
    
);

static const GlobalMemoryProgram globalProg = 
GlobalMemoryProgram("Global Memory Program Info", _sz_global_prog_source_);

TEST_F(ILMemoryTest, GlobalMemoryTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Program *prog = RuntimeTestFixture::_progMgr->loadProgram(globalProg);
    if (!prog)
    {
        ASSERT_TRUE(false);
    }

    GlobalBuffer *buf1D = 
        RuntimeTestFixture::_bufMgr->createGlobalBuffer(device, CAL_FORMAT_INT_1, 1024);

    prog->bindGlobal(buf1D);

    if (buf1D)
    {
        vector<int> cpuBuf(1024);
        util::initializeBuffer(cpuBuf, 1024, 0, 1024, util::LINEAR_INT);

        ASSERT_TRUE(buf1D->readData(&cpuBuf[0], 1024 * 1024));
        vector<int> result(1024 * 1024);
        ASSERT_TRUE(buf1D->writeData(&result[0], (unsigned long)result.size()));

        ASSERT_EQ(0, util::compareBuffers(cpuBuf, result, (unsigned long)cpuBuf.size()));

        _bufMgr->destroyBuffer(buf1D);
    }
    RuntimeTestFixture::_progMgr->unloadProgram(prog);
}