#include "CommonDefs.h"
#include "RuntimeTestFixture.h"
#include "string.h"

using namespace amdspl;
using namespace amdspl::core::cal;

typedef RuntimeTestFixture ProgramTests;

typedef ProgramInfo<1, 2, 3, 4> SampleProgamInfo;

DCL_PROGRAM_ID(SampleProgamInfo) = "Sample Program Info";
DCL_PROGRAM_SOURCE(SampleProgamInfo) = 
        "This is a test source file, I am not going to compile it.\n";

TEST_F(ProgramTests, ProgramInfoTest)
{
    ASSERT_EQ(1, SampleProgamInfo::outputs);
    ASSERT_EQ(2, SampleProgamInfo::inputs);
    ASSERT_EQ(3, SampleProgamInfo::constants);
    ASSERT_EQ(4, SampleProgamInfo::globals);

    ASSERT_TRUE(!strcmp(SampleProgamInfo::source, "This is a test source file, I am not going to compile it.\n"));
    ASSERT_TRUE(!strcmp(SampleProgamInfo::programID, "Sample Program Info"));
}

