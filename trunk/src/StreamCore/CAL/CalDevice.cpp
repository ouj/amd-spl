/****************************************************************************

Copyright (c) 2008, Advanced Micro Devices, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of Advanced Micro Devices, Inc nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

****************************************************************************/

#include "CALBase.h"
#include "CALDevice.h"

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Constructor
//! User has to initialize the device before using this device
//!
////////////////////////////////////////////////////////////////////////////////

SPLCalDevice::SPLCalDevice(unsigned short id) : _id(id), _calDevice(0),
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
SPLCalDevice::initialize()
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

SPLCalDevice::~SPLCalDevice()
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
