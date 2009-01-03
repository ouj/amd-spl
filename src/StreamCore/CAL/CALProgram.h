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
#include "ILPrograms.h"

////////////////////////////////////////////////////////////////////////////////
//!
//! \class Program
//!
//! \brief CAL backend specific implementation for Program
//!
////////////////////////////////////////////////////////////////////////////////
namespace amdspl
{
    template<unsigned int INDEX>
    class CalProgram
    {
        // IL parameter information
        typedef typename ILInfoAt<ILINFOLIST, INDEX>::Result IlInfo;

    public:
        CalProgram(CalDevice* device);
        bool initialize();

        static CalProgram<INDEX>* getInstance(void);

        CALname getConstArrayName(unsigned short i) const;
        CALname getConstName(void) const;
        CALname getInputName(unsigned short i) const;
        CALname getOutputName(unsigned short i) const;
        CALname getScatterName(void) const;
        inline const CALfunc getFunction() const;

        ~CalProgram();

    protected:

        //! \brief contains Device information for Loading pass on a specific device
        CalDevice* _device;

    private:
        static CalProgram*  _program;

        //! \brief Contains CAL specific constant array buffer name handles
        CALname              _constArrayNames[IlInfo::ConstArrayNum + 1];

        //! \brief Contains CAL specific constant buffer name handles
        CALname              _constNames;

        //! \brief input name handles
        CALname              _inputNames[IlInfo::InputNum + 1];

        //! \brief output name handles
        CALname              _outputNames[IlInfo::OutputNum + 1];

        //! \brief output name handles
        CALname              _scatterNames;

        //! \brief CAL function handle
        CALfunc _func;

        //! \brief CAL module handle
        CALmodule _module;

    };

    // Static member of program
    template<unsigned int INDEX>
    CalProgram<INDEX>* CalProgram<INDEX>::_program = NULL;

    // Singleton
    template<unsigned int INDEX>
    CalProgram<INDEX>* CalProgram<INDEX>::getInstance(void)
    {
        if (_program == NULL)
        {
            CalProgram<INDEX> *program = new CalProgram<INDEX>(CalRuntime::getInstance()->getDevice());
            if(!program->initialize())
            {
                SAFE_DELETE(program);
                return NULL;
            }
            _program = program;
        }
        return _program;
    }


    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the CAL funtion handle
    //!
    ////////////////////////////////////////////////////////////////////////////////
    template<unsigned int INDEX>
    inline const
        CALfunc
        CalProgram<INDEX>::getFunction() const
    {
        return _func;
    }

    template<unsigned int INDEX>
    CalProgram<INDEX>::CalProgram(CalDevice* device)
        : _device(device), _func(0), _module(0)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Implemet all the logic to get symbol handle and module
    //!
    //!
    ////////////////////////////////////////////////////////////////////////////////
    template<unsigned int INDEX>
    bool
        CalProgram<INDEX>::initialize()
    {
        CALdeviceinfo info = _device->getInfo();
        CALcontext ctx = _device->getContext();

        CALresult result;

        // Compiling program
        CALobject obj;

        result = calclCompile(&obj, CAL_LANGUAGE_IL, ILSources[INDEX], info.target);
        AMDSPL_CAL_RESULT_ERROR(result, "Failed to compile program\n");

        // Linking program
        CALimage image;
        result = calclLink(&image, &obj, 1);
        AMDSPL_CAL_RESULT_ERROR(result, "Failed to create image\n");

        // Load program
        result = calModuleLoad(&_module, ctx, image);
        AMDSPL_CAL_RESULT_ERROR(result, "Failed to load module\n");
        calclFreeImage(image);

        // Get function handle
        result = calModuleGetEntry(&_func, ctx, _module, "main");
        AMDSPL_CAL_RESULT_ERROR(result, "Failed to get function handle\n");

        unsigned int i = 0;
        for(i = 0; i < IlInfo::ConstArrayNum; ++i)
        {
            CALname name;
            std::ostringstream tmpStr;
            tmpStr << "cb" << i;
            result = calModuleGetName(&name, ctx, _module, tmpStr.str().c_str());
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to get name handle for constant array\n");

            _constArrayNames[i] = name;
        }

        // Get constant name handle
        if(IlInfo::ConstantNum > 0)
        {
            CALname name;
            std::ostringstream tmpStr;
            tmpStr << "cb" << i;
            result = calModuleGetName(&name, ctx, _module, tmpStr.str().c_str());
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to get name handle for constants\n");

            _constNames = name;
        }

        // Get all the input name handles
        for(unsigned int i = 0; i < IlInfo::InputNum; ++i)
        {
            CALname name;
            std::ostringstream tmpStr;
            tmpStr << "i" << i;
            result = calModuleGetName(&name, ctx, _module, tmpStr.str().c_str());
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to get name handle for input stream\n");

            _inputNames[i] = name;
        }

        // Get all the output name handles
        for(unsigned int i = 0; i < IlInfo::OutputNum; ++i)
        {
            CALname name;
            std::ostringstream tmpStr;
            tmpStr << "o" << i;
            result = calModuleGetName(&name, ctx, _module, tmpStr.str().c_str());
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to get name handle for output stream\n");

            _outputNames[i] = name;
        }

        // Get name handle for scatter stream
        if(IlInfo::ScatterNum > 0)
        {
            CALname name;
            result = calModuleGetName(&name, ctx, _module, "g[]");
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to get name handle for scatter stream\n");

            _scatterNames = name;
        }

        return true;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the constant array name handle
    //!
    //! \param i constant index
    //!
    ////////////////////////////////////////////////////////////////////////////////
    template<unsigned int INDEX>
    CALname
        CalProgram<INDEX>::getConstArrayName(unsigned short i) const
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
    template<unsigned int INDEX>
    CALname
        CalProgram<INDEX>::getConstName() const
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
    template<unsigned int INDEX>
    CALname
        CalProgram<INDEX>::getInputName(unsigned short i) const
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
    template<unsigned int INDEX>
    CALname
        CalProgram<INDEX>::getOutputName(unsigned short i) const
    {
        return _outputNames[i];
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the scatter name handle
    //!
    ////////////////////////////////////////////////////////////////////////////////
    template<unsigned int INDEX>
    CALname
        CalProgram<INDEX>::getScatterName(void) const
    {
        return _scatterNames[i];
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Destructor
    //!
    ////////////////////////////////////////////////////////////////////////////////
    template<unsigned int INDEX>
    CalProgram<INDEX>::~CalProgram()
    {
        CALcontext ctx = _device->getContext();

        // Destroy the module
        if(_module)
        {
            calModuleUnload(ctx, _module);
        }
    }
}
#endif //_CALPROGRAM_H_


