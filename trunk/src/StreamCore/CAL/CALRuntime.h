#ifndef _AMDSPL_CALRUNTIME_H_
#define _AMDSPL_CALRUNTIME_H_

////////////////////////////////////////////////////////////////////////////////
//!
//! \file CALRuntime.h
//!
//! \brief Contains the declaration of CALRuntime class
//!
////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#pragma warning (disable : 4251)
#endif

#include "ErrorCodes.h"
#include "Formats.h"

#include <cstdio>
#include <vector>

#include "cal.h"
#include "CalResourceManager.h"

typedef void(*MemoryHandler)();

class SPLCalDevice;

////////////////////////////////////////////////////////////////////////////////
//!
//! \class CALRuntime
//!
//! \brief CAL specific implementation of Runtime
//!
////////////////////////////////////////////////////////////////////////////////
namespace amdspl
{
    class SPLCalRuntime
    {
    public:
        static SPLCalRuntime* create();
        static SPLCalRuntime* getInstance();
        inline SPLCalResourceManager* getResourceManager() const;

    protected:
        SPLCalRuntime();
        bool initialize();
        ~SPLCalRuntime();

    protected:
        static SPLCalRuntime*      _runtime;
        unsigned int            _numDevices;
        SPLCalDevice*              _devices;
        SPLCalResourceManager*     _resourceMgr;

    private:
        friend BRerror getError();
        friend const char* getErrorLog();

        friend void cleanup();
    };
}
#endif //_AMDSPL_CALRUNTIME_H_
