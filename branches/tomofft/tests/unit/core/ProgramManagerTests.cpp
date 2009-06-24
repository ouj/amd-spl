#include "CommonTestDefs.h"
#include "RuntimeTestFixture.h"


using namespace amdspl;
using namespace amdspl::core::cal;

typedef RuntimeTestFixture ProgramManagerTests;

static const char *TestProgramSource = 
"This is a test source file, I am not going to compile it.\n";
static const ProgramInfo testProgInfo = 
    ProgramInfo("Test Program Info",TestProgramSource).outputs(1).inputs(2).constants(3);

static const ProgramInfo testRepProgInfo = 
    ProgramInfo("Test Replacement Program Info",TestProgramSource)
    .replaceTkn("test", "replacement test")
    .replaceTkn("compile", "run").outputs(1).inputs(2).constants(3);

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
static const ProgramInfo sampleProgram = 
    ProgramInfo("Sample Program Info", _sz_sample_prog_source_).outputs(1).inputs(1).constants(1);

TEST_F(ProgramManagerTests, ProgramInfoTest)
{
    ASSERT_EQ(1, testProgInfo._outputs);
    ASSERT_EQ(2, testProgInfo._inputs);
    ASSERT_EQ(3, testProgInfo._constants);
    ASSERT_EQ(false, testProgInfo._global);

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
