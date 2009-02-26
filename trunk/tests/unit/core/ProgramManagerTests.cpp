#include "CommonTestDefs.h"
#include "RuntimeTestFixture.h"


using namespace amdspl;
using namespace amdspl::core::cal;

typedef RuntimeTestFixture ProgramManagerTests;

typedef ProgramInfo<1, 2, 3, false> TestProgramInfo;
static const char *TestProgramSource = 
"This is a test source file, I am not going to compile it.\n";
static const TestProgramInfo testProgInfo = 
    TestProgramInfo("Test Program Info",TestProgramSource);

static const TestProgramInfo testRepProgInfo = 
    TestProgramInfo("Test Replacement Program Info",TestProgramSource)
    .replaceTkn("test", "replacement test")
    .replaceTkn("compile", "run");

typedef ProgramInfo<1, 1, 1, true> SampleProgram;
static const char* _sz_sample_prog_source_ = 
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
static const SampleProgram sampleProgram = 
    SampleProgram("Sample Program Info", _sz_sample_prog_source_);

TEST_F(ProgramManagerTests, ProgramInfoTest)
{
    ASSERT_EQ(1, testProgInfo.outputs);
    ASSERT_EQ(2, testProgInfo.inputs);
    ASSERT_EQ(3, testProgInfo.constants);
    ASSERT_EQ(0, testProgInfo.global);

    ASSERT_STREQ("This is a test source file, I am not going to compile it.\n", testProgInfo.getSource());
    ASSERT_STREQ("Test Program Info" ,testProgInfo.getID());
}

TEST_F(ProgramManagerTests, ProgramTokenReplacementTest)
{
    ASSERT_STREQ("This is a replacement test source file, I am not going to run it.\n", testRepProgInfo.getSource());
    ASSERT_STREQ("Test Replacement Program Info", testRepProgInfo.getID());
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
        ProgramManagerTests::_progMgr->loadProgram(sampleProgram, device);
    ASSERT_TRUE(prog != NULL);

    _progMgr->unloadProgram(prog);
}