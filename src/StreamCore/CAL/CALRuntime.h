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

typedef void(*MemoryHandler)();

class CalDevice;
class CalBufferMgr;
class CalProgramMgr;

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
        static CalRuntime*      create();
        static CalRuntime*      getInstance();
        inline CalBufferMgr*    getBufferMgr() const;
        inline CalProgramMgr*   getProgramMgr() const;

    protected:
        CalRuntime();
        bool initialize();
        ~CalRuntime();

    protected:
        static CalRuntime*      _runtime;
        unsigned int            _numDevices;
        CalDevice*              _devices;
        CalBufferMgr*           _bufferMgr;
        CalProgramMgr*          _programMgr;

    private:
        friend BRerror          getError();
        friend const char*      getErrorLog();

        friend void             cleanup();
    };

    
    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get back end specific buffer manager
    //!
    //! \return Device specific buffer manager handle
    //!
    ////////////////////////////////////////////////////////////////////////////////
    inline CalBufferMgr* CalRuntime::getBufferMgr() const
    {
        return _bufferMgr;
    }


    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get back end specific program manager
    //!
    //! \return Device specific program manage handle
    //!
    ////////////////////////////////////////////////////////////////////////////////
    inline CalProgramMgr* CalRuntime::getProgramMgr() const
    {
        return _programMgr;
    }
}
#endif //_AMDSPL_CALRUNTIME_H_
