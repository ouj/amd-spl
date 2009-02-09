#ifndef _AMDSPL_CALPROGRAM_DEF_H_
#define _AMDSPL_CALPROGRAM_DEF_H_

namespace amdspl
{
    template<typename ILPARALIST, unsigned int ID>
    CalProgram* CalProgram::getProgram(void)
    {
        CalProgram *program = new CalProgram(CalRuntime::getInstance()->getDevice());
        if(!program->initialize<ILParaByID<ILPARALIST, ID>::Result>())
        {
            SAFE_DELETE(program);
            return NULL;
        }
        return program;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Implemet all the logic to get symbol handle and module
    //!
    //!
    ////////////////////////////////////////////////////////////////////////////////
    template<typename ILPARAINFO>
    bool
        CalProgram::initialize()
    {
        CALdeviceinfo info = _device->getInfo();
        CALcontext ctx = _device->getContext();

        CALresult result;

        // Compiling program
        CALobject obj;

        result = calclCompile(&obj, CAL_LANGUAGE_IL, ILPARAINFO::Image, info.target);
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
        for(i = 0; i < ILPARAINFO::ConstArrayNum; ++i)
        {
            CALname name;
            std::ostringstream tmpStr;
            tmpStr << "cb" << i;
            result = calModuleGetName(&name, ctx, _module, tmpStr.str().c_str());
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to get name handle for constant array\n");

            _constArrayNames.push_back(name);
        }

        // Get constant name handle
        if(ILPARAINFO::ConstantNum > 0)
        {
            CALname name;
            std::ostringstream tmpStr;
            tmpStr << "cb" << i;
            result = calModuleGetName(&name, ctx, _module, tmpStr.str().c_str());
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to get name handle for constants\n");

            _constNames = name;
        }

        // Get all the input name handles
        for(unsigned int i = 0; i < ILPARAINFO::InputNum; ++i)
        {
            CALname name;
            std::ostringstream tmpStr;
            tmpStr << "i" << i;
            result = calModuleGetName(&name, ctx, _module, tmpStr.str().c_str());
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to get name handle for input stream\n");

            _inputNames.push_back(name);
        }

        // Get all the output name handles
        for(unsigned int i = 0; i < ILPARAINFO::OutputNum; ++i)
        {
            CALname name;
            std::ostringstream tmpStr;
            tmpStr << "o" << i;
            result = calModuleGetName(&name, ctx, _module, tmpStr.str().c_str());
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to get name handle for output stream\n");

            _outputNames.push_back(name);
        }

        // Get name handle for scatter stream
        if(ILPARAINFO::ScatterNum > 0)
        {
            CALname name;
            result = calModuleGetName(&name, ctx, _module, "g[]");
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to get name handle for scatter stream\n");

            _scatterNames = name;
        }
        return true;
    }
}

#endif // _AMDSPL_CALPROGRAM_DEF_H_