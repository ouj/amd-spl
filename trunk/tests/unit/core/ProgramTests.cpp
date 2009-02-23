#include "CommonTestDefs.h"
#include "RuntimeTestFixture.h"
#include "string.h"

using namespace amdspl;
using namespace amdspl::core::cal;

typedef RuntimeTestFixture ProgramTests;

typedef ProgramInfo<5, 3, 2, true> SampleProgram;
DCL_PROGRAM_ID(SampleProgram) = "Sample Program Info";
DCL_PROGRAM_SOURCE(SampleProgram) = 
"il_ps_2_0\n"
"dcl_output_generic o0\n"
"dcl_output_generic o1\n"
"dcl_output_generic o2\n"
"dcl_output_generic o3\n"
"dcl_output_generic o4\n"
"dcl_input_position_interp(linear_noperspective) v0.xy__\n"
"dcl_resource_id(0)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
"dcl_resource_id(1)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
"dcl_resource_id(2)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
"dcl_cb cb0[1]\n"
"dcl_cb cb1[2]\n"
"sample_resource(0)_sampler(0) r1, v0.xy00\n"
"mov g[r1.x], r1.y000\n"
"add o0, r1, cb0[0]\n"
"endmain\n"
"end\n";

TEST_F(ProgramTests, GetNameTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Program *prog = 
        ProgramTests::_progMgr->loadProgram<SampleProgram>(device);
    if(prog != NULL)
    {
        for (unsigned int i = 0; i < SampleProgram::inputs; i++)
        {
            ASSERT_TRUE(prog->getInputName(i) != 0);
        }
        for (unsigned int i = 0; i < SampleProgram::outputs; i++)
        {
            ASSERT_TRUE(prog->getOutputName(i) != 0);
        }
        for (unsigned int i = 0; i < SampleProgram::constants; i++)
        {
            ASSERT_TRUE(prog->getConstName(i) != 0);
        }
        if (SampleProgram::global)
        {
            ASSERT_TRUE(prog->getGlobalName() != 0);
        }
    }

    _progMgr->unloadProgram(prog);
}

typedef ProgramInfo<1, 1, 0, true> CopyProgram;
DCL_PROGRAM_ID(CopyProgram) = "Copy Program Info";
DCL_PROGRAM_SOURCE(CopyProgram) = 
"il_ps_2_0\n"
"dcl_output_generic o0\n"
"dcl_input_position_interp(linear_noperspective) v0.xy__\n"
"dcl_resource_id(0)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
"sample_resource(0)_sampler(0) o0, v0.xy00\n"
"endmain\n"
"end\n";

TEST_F(ProgramTests, BindBufferTest1)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);

    Buffer *buf1 = _bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_2, 1024, 1);
    ASSERT_TRUE(buf1 != NULL);
    Buffer *buf2 = _bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_2, 1024, 1);
    ASSERT_TRUE(buf1 != NULL);

    Program *prog = 
        ProgramTests::_progMgr->loadProgram<SampleProgram>(device);
    if(prog != NULL)
    {
        ASSERT_TRUE(prog->bindInput(buf1, 0));
        ASSERT_TRUE(prog->bindOutput(buf2, 0));
    }

    ASSERT_TRUE(prog->unbindInput(0));
    ASSERT_TRUE(prog->unbindOutput(0));

    _bufMgr->destroyBuffer(buf1);
    _bufMgr->destroyBuffer(buf2);
    _progMgr->unloadProgram(prog);
}

TEST_F(ProgramTests, RunProgramTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);

    Buffer *buf1 = _bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_2, 1024, 1);
    ASSERT_TRUE(buf1 != NULL);
    Buffer *buf2 = _bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_2, 1024, 1);
    ASSERT_TRUE(buf1 != NULL);

    vector<float2> buffer1(1024);
    util::initializeBuffer(buffer1, 1024, 1, 1024, util::RANDOM);
    buf1->readData(&buffer1[0], buffer1.size());

    Program *prog = 
        ProgramTests::_progMgr->loadProgram<SampleProgram>(device);
    if(prog != NULL)
    {
        ASSERT_TRUE(prog->bindInput(buf1, 0));
        ASSERT_TRUE(prog->bindOutput(buf2, 0));
    }

    ASSERT_TRUE(prog->unbindInput(0));
    ASSERT_TRUE(prog->unbindOutput(0));

    vector<float2> buffer2(1024);
    buf2->writeData(&buffer2[0], buffer2.size());
    
    util::compareBuffers(buffer1, buffer2, buffer1.size());

    _progMgr->unloadProgram(prog);
    _bufMgr->destroyBuffer(buf1);
    _bufMgr->destroyBuffer(buf2);
}