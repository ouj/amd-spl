#include "calcl.h"
#include "CALProgram.h"
#include "CALDevice.h"
#include "KernelDesc.h"
#include "CALBase.h"

#include <iostream>
#include <sstream>
#include <string>

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Constructor
//!
//! \param pass Associated pass
//! \param device Associated CALdevice
//!
////////////////////////////////////////////////////////////////////////////////
namespace amdspl
{
    CalProgram::CalProgram(Pass& pass, CalDevice* device)
        : _pass(pass), _device(device), _func(0), _module(0)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Implemet all the logic to get symbol handle and module
    //!
    //!
    ////////////////////////////////////////////////////////////////////////////////

    bool
        CalProgram::initialize()
    {
        CALdeviceinfo info = _device->getInfo();
        CALcontext ctx = _device->getContext();

        CALresult result;

        // Compiling program
        CALobject obj;

        result = calclCompile(&obj, CAL_LANGUAGE_IL, _pass.Image, info.target);
        CAL_RESULT_ERROR(result, "Failed to compile program\n");

        // Linking program
        CALimage image;
        result = calclLink(&image, &obj, 1);
        CAL_RESULT_ERROR(result, "Failed to create image\n");

        // Load program
        result = calModuleLoad(&_module, ctx, image);
        CAL_RESULT_ERROR(result, "Failed to load module\n");
        calclFreeImage(image);

        // Get function handle
        result = calModuleGetEntry(&_func, ctx, _module, "main");
        CAL_RESULT_ERROR(result, "Failed to get function handle\n");

        unsigned int i = 0;
        for(i = 0; i < _pass.ConstArrays->size(); ++i)
        {
            CALname name;
            std::ostringstream tmpStr;
            tmpStr << "cb" << i;
            result = calModuleGetName(&name, ctx, _module, tmpStr.str().c_str());
            CAL_RESULT_ERROR(result, "Failed to get name handle for constant array\n");

            _constNames.push_back(name);
        }

        // Get constant name handle
        if(_pass.Constants->size() > 0)
        {
            CALname name;
            std::ostringstream tmpStr;
            tmpStr << "cb" << i;
            result = calModuleGetName(&name, ctx, _module, tmpStr.str().c_str());
            CAL_RESULT_ERROR(result, "Failed to get name handle for constants\n");

            _constNames.push_back(name);
        }

        // Get all the input name handles
        for(unsigned int i = 0; i < _pass.Inputs->size(); ++i)
        {
            CALname name;
            std::ostringstream tmpStr;
            tmpStr << "i" << i;
            result = calModuleGetName(&name, ctx, _module, tmpStr.str().c_str());
            CAL_RESULT_ERROR(result, "Failed to get name handle for input stream\n");

            _inputNames.push_back(name);
        }

        // Get all the output name handles
        for(unsigned int i = 0; i < _pass.Outputs->size(); ++i)
        {
            CALname name;
            std::ostringstream tmpStr;
            tmpStr << "o" << i;
            result = calModuleGetName(&name, ctx, _module, tmpStr.str().c_str());
            CAL_RESULT_ERROR(result, "Failed to get name handle for output stream\n");

            _outputNames.push_back(name);
        }

        // Get name handle for scatter stream
        if(_pass.Scatters->size() > 0)
        {
            CALname outputName;
            result = calModuleGetName(&outputName, ctx, _module, "g[]");
            CAL_RESULT_ERROR(result, "Failed to get name handle for scatter stream\n");

            _outputNames.push_back(outputName);
        }

        return true;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the constant name handle
    //!
    //! \param i constant indxex
    //!
    ////////////////////////////////////////////////////////////////////////////////

    CALname
        CalProgram::getConstName(unsigned short i) const
    {
        return _constNames[i];
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the input name handle
    //!
    //! \param i input indxex
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