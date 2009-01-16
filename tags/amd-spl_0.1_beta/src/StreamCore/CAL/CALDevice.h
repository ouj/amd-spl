#ifndef _AMDSPL_CALDEVICE_H_
#define _AMDSPL_CALDEVICE_H_

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
namespace amdspl
{

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

}
#endif //_CALDEVICE_H_
