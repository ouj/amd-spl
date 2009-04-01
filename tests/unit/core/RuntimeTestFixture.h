#ifndef _RUNTIME_TEST_FIXTURE_H_
#define _RUNTIME_TEST_FIXTURE_H_
#include "gtest/gtest.h"
#include "Runtime.h"
#include "DeviceManager.h"
#include "BufferManager.h"

using namespace amdspl::core::cal;

class RuntimeTestFixture : public testing::Test
{
public:
    RuntimeTestFixture(void);
    ~RuntimeTestFixture(void);

    static void SetUpTestCase();
    static void TearDownTestCase();

    void SetUp();
    void TearDown();

    static Runtime* _runtime;
    static BufferManager* _bufMgr;
    static DeviceManager* _deviceMgr;
    static ProgramManager* _progMgr;
};
#endif
