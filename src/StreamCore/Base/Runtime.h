#ifndef _RUNTIME_H_
#define _RUNTIME_H_

////////////////////////////////////////////////////////////////////////////////
//!
//! \file Runtime.h
//!
//! \brief Contains the declaration of Runtime class
//!
////////////////////////////////////////////////////////////////////////////////

#include <vector>

#ifdef WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

//  The warning disables visual studio's
//  annoying habit of warning when using the standard set lib
#ifdef WIN32
#pragma warning (disable : 4251)
#endif

#include "ErrorCodes.h"
#include "Formats.h"

class Device;
class ExecMgr;
class BufferMgr;
class KernelOracle;
class StreamOracle;
class StreamImpl;
class ConstImpl;

typedef void(*MemoryHandler)();

namespace amdspl
{
    EXPORT void setMemoryHandle(MemoryHandler handle);

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Abstract class represnting Runtime for backend.
//! A singleton that makes sure all the creation routine for stream and 
//! kernel goes to the correct backend.
//! 
//! Construction - Constructed as soon as any new stream is created.
//! 
//! Destruction - Destroyed once application exits.
//! 
//! Interaction - Contains a set of devices representing all the devices available
//! and asscociated Oracle and Mgr classes.
//! 
//! Error Conditions - It can Fail to initialize a particular backend. 
//! 
////////////////////////////////////////////////////////////////////////////////

class EXPORT Runtime
{
    public:

        static Runtime* getInstance();

        inline KernelOracle* getKernelOracle() const;
        inline StreamOracle* getStreamOracle() const;
        inline BufferMgr* getBufferMgr() const;
        inline ExecMgr* getExecMgr() const;

        //virtual StreamImpl* createStreamImpl(unsigned short rank, unsigned int* dimensions,
        //                             BRformat* format, unsigned int count);

        virtual const char* getRuntimeString() const = 0;

    protected:

            Runtime();
            virtual bool initialize() = 0;
            virtual ~Runtime();

    protected:

        //! \brief Static instance of singleton class
        static Runtime* _runtime;

        //! \brief Number of devices visible
        unsigned int _numDevices;

        //! \brief Contains the list of devices that a developer might want to use
        std::vector<Device*> _devices;

        //! \brief Container of BufferMgr
        //! There is one BufferMgr per device
        std::vector<BufferMgr*> _bufferMgrs;

        //! \brief Container of ExecMgr
        //! There is one ExecMgr per device
        std::vector<ExecMgr*> _execMgrs;

        //! \brief Acces to StreamOracle is through Runtime
        //! There is one StreamOracle per device
        std::vector<StreamOracle*> _streamOracles;

        //! \brief Acces to KernelOracle is through Runtime
        //! There is one KernelOracle per device
        std::vector<KernelOracle*> _kernelOracles;

    private:

        friend BRerror getError();
        friend const char* getErrorLog();

        friend void cleanup();

};

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Get backend specifc KernelOracle
//!
//! \return KernelOracle handle
//!
////////////////////////////////////////////////////////////////////////////////

inline
KernelOracle*
Runtime::getKernelOracle() const
{
    return _kernelOracles[0];
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Get backend specifc StreamOracle
//!
//! \return StreamOracle handle
//!
////////////////////////////////////////////////////////////////////////////////

inline
StreamOracle*
Runtime::getStreamOracle() const
{
    return _streamOracles[0];
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Get backend specifc BufferMgr
//!
//! \return Device specifc BufferMgr handle
//!
////////////////////////////////////////////////////////////////////////////////

inline
BufferMgr* 
Runtime::getBufferMgr() const
{
    return _bufferMgrs[0];
}


////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Get backend specifc ExecMgr
//!
//! \return Device specifc ExecMgr handle
//!
////////////////////////////////////////////////////////////////////////////////

inline
ExecMgr*
Runtime::getExecMgr() const
{
    return _execMgrs[0];
}

} //end namespace brook

#endif //_RUNTIME_H_
