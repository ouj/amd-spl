#ifndef _AMDSPL_CALPROGRAM_DEF_H_
#define _AMDSPL_CALPROGRAM_DEF_H_

namespace amdspl
{

    //! \brief Static member of CALProgram, to be used as the singleton
    template<typename ILPARAINFO>
    CalProgram<ILPARAINFO>* CalProgram<ILPARAINFO>::_program = NULL;

    //! \brief Singleton
    template<typename ILPARAINFO>
    CalProgram<ILPARAINFO>* CalProgram<ILPARAINFO>::getInstance(void)
    {
        if (_program == NULL)
        {
            CalProgram<ILPARAINFO> *program = new CalProgram<ILPARAINFO>(CalRuntime::getInstance()->getDevice());
            if(!program->initialize())
            {
                SAFE_DELETE(program);
                return NULL;
            }
            _program = program;
        }
        return _program;
    }

    template<typename ILPARAINFO>
    bool CalProgram<ILPARAINFO>::executeProgram(const CALdomain &rect)
    {
        _constBuffer->setDataToBuffer();
        CALcontext ctx = _device->getContext();
        CALfunc func = getFunction();
        // Run the kernel on GPU
        AMDSPL_CAL_RESULT_ERROR(calCtxRunProgram(&_execEvent, ctx, func, &rect), "Error to run program");

        calCtxIsEventDone(ctx, _execEvent);
        return true;
    }

    template<typename ILPARAINFO>
    void CalProgram<ILPARAINFO>::waitDoneEvent(void) const
    {
        CALcontext ctx = _device->getContext();
        while(calCtxIsEventDone(ctx, _execEvent));
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the CAL funtion handle
    //!
    ////////////////////////////////////////////////////////////////////////////////
    template<typename ILPARAINFO>
    inline const
        CALfunc
        CalProgram<ILPARAINFO>::getFunction() const
    {
        return _func;
    }

    template<typename ILPARAINFO>
    CalProgram<ILPARAINFO>::CalProgram(CalDevice* device)
        : _device(device), _func(0), _module(0), _constBuffer(0)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Implemet all the logic to get symbol handle and module
    //!
    //!
    ////////////////////////////////////////////////////////////////////////////////
    template<typename ILPARAINFO>
    bool
        CalProgram<ILPARAINFO>::initialize()
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

            _constArrayNames[i] = name;
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

            _inputNames[i] = name;
        }

        // Get all the output name handles
        for(unsigned int i = 0; i < ILPARAINFO::OutputNum; ++i)
        {
            CALname name;
            std::ostringstream tmpStr;
            tmpStr << "o" << i;
            result = calModuleGetName(&name, ctx, _module, tmpStr.str().c_str());
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to get name handle for output stream\n");

            _outputNames[i] = name;
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

    template<typename ILPARAINFO>
    CalConstBuffer<ILPARAINFO::ConstantNum>* 
        CalProgram<ILPARAINFO>::getConstantBuffer(void)
    {
        if (_constBuffer == NULL)
        {
            _constBuffer = CalConstBuffer<ILPARAINFO::ConstantNum>::createConstBuffer();
        }
        return _constBuffer;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the constant array name handle
    //!
    //! \param i constant index
    //!
    ////////////////////////////////////////////////////////////////////////////////
    template<typename ILPARAINFO>
    CALname
        CalProgram<ILPARAINFO>::getConstArrayName(unsigned short i) const
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
    template<typename ILPARAINFO>
    CALname
        CalProgram<ILPARAINFO>::getConstName() const
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
    template<typename ILPARAINFO>
    CALname
        CalProgram<ILPARAINFO>::getInputName(unsigned short i) const
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
    template<typename ILPARAINFO>
    CALname
        CalProgram<ILPARAINFO>::getOutputName(unsigned short i) const
    {
        return _outputNames[i];
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Get the scatter name handle
    //!
    ////////////////////////////////////////////////////////////////////////////////
    template<typename ILPARAINFO>
    CALname
        CalProgram<ILPARAINFO>::getScatterName(void) const
    {
        return _scatterNames[i];
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Destructor
    //!
    ////////////////////////////////////////////////////////////////////////////////
    template<typename ILPARAINFO>
    CalProgram<ILPARAINFO>::~CalProgram()
    {
        SAFE_DELETE(_constBuffer);
        CALcontext ctx = _device->getContext();

        // Destroy the module
        if(_module)
        {
            calModuleUnload(ctx, _module);
        }
    }
}

#endif // _AMDSPL_CALPROGRAM_DEF_H_