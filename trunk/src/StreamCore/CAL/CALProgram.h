#ifndef _CALPROGRAM_H_
#define _CALPROGRAM_H_

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
//! \file CALProgram.h
//!
//! \brief Contains the declaration of CALProgram class
//!
////////////////////////////////////////////////////////////////////////////////

#include "cal.h"
#include "Program.h"
#include <vector>

class CALDevice;

////////////////////////////////////////////////////////////////////////////////
//!
//! \class Program
//!
//! \brief CAL backend specific implementation for Program
//!
////////////////////////////////////////////////////////////////////////////////

class CALProgram : public Program
{
    public:
        CALProgram(Pass& pass, Device* device);
        bool initialize();

        CALname getConstName(unsigned short i) const;
        CALname getInputName(unsigned short i) const;
        CALname getOutputName(unsigned short i) const;
        inline const CALfunc getFunction() const;

        ~CALProgram();


    private:

        //! \brief Contains CAL specific constant buffer name handles
        std::vector<CALname> _constNames;

        //! \brief input name handles
        std::vector<CALname> _inputNames;

        //! \brief output name handles
        std::vector<CALname> _outputNames;

        //! \brief CAL function handle
        CALfunc _func;

        //! \brief CAL module handle
        CALmodule _module;

};

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Get the CAL funtion handle
//!
////////////////////////////////////////////////////////////////////////////////

inline const
CALfunc
CALProgram::getFunction() const
{
    return _func;
}

#endif //_CALPROGRAM_H_
