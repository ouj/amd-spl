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
#include <vector>
#include "KernelDesc.h"

class CalDevice;

////////////////////////////////////////////////////////////////////////////////
//!
//! \class Program
//!
//! \brief CAL backend specific implementation for Program
//!
////////////////////////////////////////////////////////////////////////////////
namespace amdspl
{

    class CalProgram
    {
    public:
        CalProgram(Pass& pass, CalDevice* device);
        bool initialize();

        CALname getConstName(unsigned short i) const;
        CALname getInputName(unsigned short i) const;
        CALname getOutputName(unsigned short i) const;
        inline const CALfunc getFunction() const;

        ~CalProgram();

        inline const Pass* getPass() const;


    protected:
        //! \brief Contains the information of Pass that this program corresponds to
        Pass _pass;

        //! \brief contains Device information for Loading pass on a specific device
        CalDevice* _device;

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

    inline const
        Pass*
        CalProgram::getPass() const
    {
        return &_pass;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the CAL funtion handle
    //!
    ////////////////////////////////////////////////////////////////////////////////

    inline const
        CALfunc
        CalProgram::getFunction() const
    {
        return _func;
    }

}
#endif //_CALPROGRAM_H_


