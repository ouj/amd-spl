#include "CommonDefs.h"
#include "RuntimeTestFixture.h"


using namespace amdspl;
using namespace amdspl::core::cal;

TEST_F(RuntimeTestFixture, LocalBufferTypeCastTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_4, 1024);

    LocalBuffer *localBuf = 
        dynamic_cast<LocalBuffer*>(buf);
    ASSERT_TRUE(localBuf != NULL);

    _bufMgr->destroyBuffer(localBuf);
}

TEST_F(RuntimeTestFixture, LocalBufferGetPropertiesTest)
{
    Device* device = _deviceMgr->getDefaultDevice();
    if(!device)
        return;

    Buffer *buf = 
        RuntimeTestFixture::_bufMgr->createLocalBuffer(device, CAL_FORMAT_FLOAT_4, 1024);

    if (!buf)
    {
        ASSERT_TRUE(buf->getResHandle() != 0);
        ASSERT_TRUE(buf->getFormat() == CAL_FORMAT_FLOAT_4);
        ASSERT_TRUE(buf->getWidth() == 1024);
        ASSERT_TRUE(buf->getHeight() == 0);
    }

    _bufMgr->destroyBuffer(buf);
}
