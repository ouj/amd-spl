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
#include "ILProgInfo.h"

////////////////////////////////////////////////////////////////////////////////
//!
//! \class Program
//!
//! \brief CAL backend specific implementation for Program
//!
////////////////////////////////////////////////////////////////////////////////
namespace amdspl
{
    class CalDevice;
    class CalProgram
    {
    public:
        CalProgram(const ILProgInfo& pass, CalDevice* device);
        bool initialize();

        CALname getConstName(unsigned short i) const;
        CALname getInputName(unsigned short i) const;
        CALname getOutputName(unsigned short i) const;
        inline const CALfunc getFunction() const;

        ~CalProgram();

        inline const ILProgInfo* getPass() const;


    protected:
        //! \brief Contains the information of Pass that this program corresponds to
        ILProgInfo _ilInfo;

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
        ILProgInfo*
        CalProgram::getPass() const
    {
        return &_ilInfo;
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


