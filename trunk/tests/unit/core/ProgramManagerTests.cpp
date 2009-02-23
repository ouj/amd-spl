#include "CommonTestDefs.h"
#include "RuntimeTestFixture.h"


using namespace amdspl;
using namespace amdspl::core::cal;

typedef RuntimeTestFixture ProgramManagerTests;

typedef ProgramInfo<1, 2, 3, false> TestProgamInfo;

DCL_PROGRAM_ID(TestProgamInfo) = "Test Program Info";
DCL_PROGRAM_SOURCE(TestProgamInfo) = 
"This is a test source file, I am not going to compile it.\n";

typedef ProgramInfo<1, 1, 1, true> SampleProgram;
DCL_PROGRAM_ID(SampleProgram) = "Sample Program Info";
DCL_PROGRAM_SOURCE(SampleProgram) = 
"il_ps_2_0\n"
"dcl_output_generic o0\n"
"dcl_input_position_interp(linear_noperspective) v0.xy__\n"
"dcl_resource_id(0)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
"dcl_cb cb0[1]\n"
"sample_resource(0)_sampler(0) r1, v0.xy00\n"
"mov g[r1.x], r1.y000\n"
"add o0, r1, cb0[0]\n"
"endmain\n"
"end\n";

TEST_F(ProgramManagerTests, ProgramInfoTest)
{
    ASSERT_EQ(1, TestProgamInfo::outputs);
    ASSERT_EQ(2, TestProgamInfo::inputs);
    ASSERT_EQ(3, TestProgamInfo::constants);
    ASSERT_EQ(false, TestProgamInfo::global);

    ASSERT_TRUE(!strcmp(TestProgamInfo::source, "This is a test source file, I am not going to compile it.\n"));
    ASSERT_TRUE(!strcmp(TestProgamInfo::programID, "Test Program Info"));
}


TEST_F(ProgramManagerTests, GetProgramManagerTest)
{
    ASSERT_TRUE(ProgramManagerTests::_runtime->getProgramManager());
}

TEST_F(ProgramManagerTests, LoadUnloadProgramTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    ASSERT_TRUE(device);
    Program *prog = 
        ProgramManagerTests::_progMgr->loadProgram<SampleProgram>(device);
    ASSERT_TRUE(prog != NULL);

    _progMgr->unloadProgram(prog);
}