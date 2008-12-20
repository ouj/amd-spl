#include "CALBase.h"
#include "CALDevice.h"

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Constructor
//! User has to initialize the device before using this device
//!
////////////////////////////////////////////////////////////////////////////////

CalDevice::CalDevice(unsigned short id) : _id(id), _calDevice(0),
                                          _calContext(0)
{
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief initializes the CALDevice.
//!
//! \return flag saying initialization was proper or not
//!
////////////////////////////////////////////////////////////////////////////////

bool
CalDevice::initialize()
{
    //All the device specifc initialization
    CALresult result;
    result = calDeviceOpen(&_calDevice, _id);
    CHECK_CAL_RESULT(result, "Failed to open CAL device \n");

    result = calDeviceGetInfo(&_calDeviceInfo, _id);
    CHECK_CAL_RESULT(result, "Failed to get info on CAL device \n");

    _calDeviceAttribs.struct_size = sizeof(CALdeviceattribs);
    result = calDeviceGetAttribs(&_calDeviceAttribs, _id);
    CHECK_CAL_RESULT(result, "Failed to get CAL device attributes\n");

    // Create the device context
    result = calCtxCreate(&_calContext, _calDevice);
    CHECK_CAL_RESULT(result, "Failed to create context on CAL device \n");

    return true;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Destructor
//! cleanup the device.
//!
////////////////////////////////////////////////////////////////////////////////

CalDevice::~CalDevice()
{
    // Cleanup of context and Device handle
    if(_calContext)
    {
        calCtxDestroy(_calContext);
    }

    if(_calDevice)
    {
        calDeviceClose(_calDevice);
    }
}
