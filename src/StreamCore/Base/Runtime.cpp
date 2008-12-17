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

#include<iostream>
#include<cstdlib>
#include<new>

#include "Runtime.h"
//#include "ConstImpl.h"
#include "CALRuntime.h"
//#include "cpu.hpp"
//#include "KernelOracle.h"
//#include "StreamOracle.h"
//#include "BufferMgr.h"
//#include "ExecMgr.h"
#include "Device.h"

namespace amdspl
{

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Default handler that is used in case user has not provided any hadler
    //! Gives a warning and throws bad_alloc exception. So the user gets opportunity 
    //! to handle this exception in case he has not provided a callback.
    //!
    ////////////////////////////////////////////////////////////////////////////////

    void defaultHandler()
    {
        std::cout << "Failed to allocate memory.\n";
        throw std::bad_alloc();
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Function to set memory handle
    //!
    ////////////////////////////////////////////////////////////////////////////////

    void
    setMemoryHandle(MemoryHandler handler)
    {
        std::set_new_handler(handler);
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Function regestered in atexit call
    //!
    //! A friend function that calls runtime destructor.
    //! This function is called as soon as application exits.
    //!
    ////////////////////////////////////////////////////////////////////////////////

    void
    cleanup()
    {
        Runtime*& runtime = Runtime::_runtime;
        if (runtime != NULL)
        {
            delete runtime;
            runtime = NULL;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Static instance of singleton class
    //!
    ////////////////////////////////////////////////////////////////////////////////

    Runtime* Runtime::_runtime = NULL;

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Constructor
    //!
    ////////////////////////////////////////////////////////////////////////////////

    Runtime::Runtime()
            :_numDevices(0)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Static method to get Runtime Instance.
    //!
    //! Calls Create method on backend runtime if instance is NULL.
    //!
    ////////////////////////////////////////////////////////////////////////////////

    Runtime* 
    Runtime::getInstance()
    {
        if (_runtime == NULL)
        {
            MemoryHandler oldHandle = std::set_new_handler(defaultHandler);
            if(oldHandle)
            {
                std::set_new_handler(oldHandle);
            }

            _runtime = CALRuntime::create();

            if(_runtime == NULL)
            {
                std::cout << "Failed to initialize CAL runtime, falling back to CPU\n";
                if(_runtime == NULL)
                {
                    std::cout << "Failed to initialize the runtime. Application exiting\n";
                    exit(1);
                }
            }

            // Register the callback for application exit
            // to make sure we cleanup everything
            atexit(cleanup);
        }

        return _runtime;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Destructor
    //!
    ////////////////////////////////////////////////////////////////////////////////

    Runtime::~Runtime()
    {
        for(CALuint i = 0; i < _bufferMgrs.size(); ++i)
        {
            delete _bufferMgrs[i];
            delete _execMgrs[i];
            delete _kernelOracles[i];
            delete _streamOracles[i];
            delete _devices[i];
        }
    }

    //////////////////////////////////////////////////////////////////////////////////
    ////!
    ////! \brief Method to create StreamImpl given required parameters
    ////!
    //////////////////////////////////////////////////////////////////////////////////

    //StreamImpl* 
    //Runtime::createStreamImpl(unsigned short rank, 
    //                          unsigned int* dimensions, BRformat* format, unsigned int count)
    //{
    //    StreamOracle* oracle = getStreamOracle();

    //    return oracle->createStreamImpl(rank, dimensions, format, count);
    //}
}
