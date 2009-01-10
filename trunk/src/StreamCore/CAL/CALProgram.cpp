#ifndef _AMDSPL_CALPROGRAM_DEF_H_
#define _AMDSPL_CALPROGRAM_DEF_H_

#include "CALProgram.h"

namespace amdspl
{
    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Execute the program in domain
    //!
    //////////////////////////////////////////////////////////////////////////
    bool CalProgram::executeProgram(const CALdomain &rect)
    {
        CALcontext ctx = _device->getContext();
        CALfunc func = getFunction();
        // Run the kernel on GPU
        AMDSPL_CAL_RESULT_ERROR(calCtxRunProgram(&_execEvent, ctx, func, &rect), "Error to run program");

        CALresult res = calCtxIsEventDone(ctx, _execEvent);
        return true;
    }

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Wait for the done event
    //!
    //////////////////////////////////////////////////////////////////////////
    void CalProgram::waitDoneEvent(void) const
    {
        CALcontext ctx = _device->getContext();
        while(calCtxIsEventDone(ctx, _execEvent));
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

    CalProgram::CalProgram(CalDevice* device)
        : _device(device), _func(0), _module(0)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the constant array name handle
    //!
    //! \param i constant index
    //!
    ////////////////////////////////////////////////////////////////////////////////
    CALname
        CalProgram::getConstArrayName(unsigned short i) const
    {
        return _constArrayNames[i];
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the constant name handle
    //!
    //! \param i constant index
    //!
    ////////////////////////////////////////////////////////////////////////////////
    CALname
        CalProgram::getConstName() const
    {
        return _constNames;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the input name handle
    //!
    //! \param i input index
    //!
    ////////////////////////////////////////////////////////////////////////////////
    CALname
        CalProgram::getInputName(unsigned short i) const
    {
        return _inputNames[i];
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the output name handle
    //!
    //! \param i output indxex
    //!
    ////////////////////////////////////////////////////////////////////////////////
    CALname
        CalProgram::getOutputName(unsigned short i) const
    {
        return _outputNames[i];
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the scatter name handle
    //!
    ////////////////////////////////////////////////////////////////////////////////
    CALname
        CalProgram::getScatterName(void) const
    {
        return _scatterNames;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Destructor
    //!
    ////////////////////////////////////////////////////////////////////////////////
    CalProgram::~CalProgram()
    {
        CALcontext ctx = _device->getContext();

        // Destroy the module
        if(_module)
        {
            calModuleUnload(ctx, _module);
        }
    }
}

#endif // _AMDSPL_CALPROGRAM_DEF_H_