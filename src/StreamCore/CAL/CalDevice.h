#ifndef _AMDSPL_CALDEVICE_H_
#define _AMDSPL_CALDEVICE_H_

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

////////////////////////////////////////////////////////////////////////////////
//!
//! \file CALDevice.h
//!
//! \brief Contains the declaration of CALDevice class
//!
////////////////////////////////////////////////////////////////////////////////

#include <cstdio>

#include "cal.h"
#include "CalDevice.h"

////////////////////////////////////////////////////////////////////////////////
//!
//! \class CALDevice
//!
//! \brief A class that encapsulate all the device specific data.
//! (Device handle, context)
//!
////////////////////////////////////////////////////////////////////////////////

class CalDevice
{
    public:
        explicit CalDevice(unsigned short id);
        bool initialize();
        inline CALdevice getDevice() const;
        inline CALdeviceinfo getInfo() const;
        inline CALdeviceattribs getAttribs() const;
        inline CALcontext getContext() const;
        ~CalDevice();

protected:
    //! \brief User ID of the device
    unsigned short _id;
    private:

        //! \brief CALdevice handle
        CALdevice _calDevice;

        //! \brief CALdevice info properties
        CALdeviceinfo _calDeviceInfo;

        //! \brief CALdevice attrib properties
        CALdeviceattribs _calDeviceAttribs;

        //! \brief Other Device spefic handles.
        //! For CAL it is CALcontext
        CALcontext _calContext;
};

inline
CALdevice
CalDevice::getDevice() const
{
    return _calDevice;
}

inline
CALdeviceinfo
CalDevice::getInfo() const
{
  return _calDeviceInfo;
}

inline
CALdeviceattribs
CalDevice::getAttribs() const
{
  return _calDeviceAttribs;
}

inline
CALcontext
CalDevice::getContext() const
{
  return _calContext;
}

#endif //_CALDEVICE_H_
