#ifndef _AMDSPL_CALPROGRAM_H_
#define _AMDSPL_CALPROGRAM_H_

////////////////////////////////////////////////////////////////////////////////
//!
//! \file CALProgram.h
//!
//! \brief Contains the declaration of CALProgram class
//!
////////////////////////////////////////////////////////////////////////////////

#include "cal.h"
#include "calcl.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "CALBase.h"
#include "CALDevice.h"
#include "CALRuntime.h"
#include "CALConstBuffer.h"

////////////////////////////////////////////////////////////////////////////////
//!
//! \class Program
//!
//! \brief CAL back-end specific implementation for Program
//!
////////////////////////////////////////////////////////////////////////////////
namespace amdspl
{
    template<typename ILPARAINFO>
    class CalProgram
    {
    protected:
        CalProgram(CalDevice* device);
    public:
        bool initialize();
        void cleanup();

        static CalProgram<ILPARAINFO>* getInstance(void);

        bool    executeProgram(const CALdomain &rect);
        CALname getConstArrayName(unsigned short i) const;
        CALname getConstName(void) const;
        CALname getInputName(unsigned short i) const;
        CALname getOutputName(unsigned short i) const;
        CALname getScatterName(void) const;
        inline const CALfunc getFunction() const;

        void    waitDoneEvent(void) const;
        ~CalProgram();

        CalConstBuffer<ILPARAINFO::ConstantNum>*
                getConstantBuffer(void);

    protected:

        //! \brief Contains device information for loading program on a specific device
        CalDevice*           _device;

        //! \brief Contains context information for executing program on a specific device
        CALcontext           _ctx;
    private:
        CalConstBuffer<ILPARAINFO::ConstantNum>*
                             _constBuffer;

        //! \brief Singleton static member of CalProgram.
        static CalProgram*   _program;

        //! \brief Contains CAL IL source string;
        const char*          _image;     

        //! \brief Contains CAL specific constant array buffer name handles
        CALname              _constArrayNames[ILPARAINFO::ConstArrayNum + 1];

        //! \brief Contains CAL specific constant buffer name handles
        CALname              _constNames;

        //! \brief input name handles
        CALname              _inputNames[ILPARAINFO::InputNum + 1];

        //! \brief output name handles
        CALname              _outputNames[ILPARAINFO::OutputNum + 1];

        //! \brief output name handles
        CALname              _scatterNames;

        //! \brief CAL function handle
        CALfunc              _func;

        //! \brief CAL module handle
        CALmodule            _module;

        //! \brief execution event of the program;
        CALevent             _execEvent;
    };
}

#include "CALProgramDef.h"

#endif //_CALPROGRAM_H_


