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
#include "CALBufferMgr.h"

#include "cal.h"

typedef void(*MemoryHandler)();

class CalDevice;

////////////////////////////////////////////////////////////////////////////////
//!
//! \class CALRuntime
//!
//! \brief CAL specific implementation of Runtime
//!
////////////////////////////////////////////////////////////////////////////////
namespace amdspl
{
    class CalRuntime
    {
    public:
        static CalRuntime* create();
        static CalRuntime* getInstance();
        CalBufferMgr*      getBufferManager() const;

    protected:
        CalRuntime();
        bool initialize();
        ~CalRuntime();

    protected:
        static CalRuntime*      _runtime;
        unsigned int            _numDevices;
        CalDevice*              _devices;
        CalBufferMgr*           _bufferMgr;

    private:
        friend BRerror getError();
        friend const char* getErrorLog();

        friend void cleanup();
    };
}
#endif //_AMDSPL_CALRUNTIME_H_
