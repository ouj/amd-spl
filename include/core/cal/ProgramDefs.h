#ifndef AMDSPL_PROGRAM_DEFS_H
#define AMDSPL_PROGRAM_DEFS_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		ProgramDefs.h
//!	\date 		1:3:2009   14:45
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains inline and template definition of Program class.
//!
//////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
#pragma warning(disable : 4996)
#endif

#include <assert.h>
namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	i       The index of the output register.
            //! \return	CALname The CAL name of the output register.
            //!
            //! \brief	Get CAL name of a output register.
            //!
            //////////////////////////////////////////////////////////////////////////
            inline CALname Program::getOutputName(unsigned short i) const
            {
                assert(i <= _outputNames.size());
                return _outputNames[i];
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	i       The index of the input register.
            //! \return	CALname The CAL name of the input register.
            //!
            //! \brief	Get CAL name of a input register.
            //!
            //////////////////////////////////////////////////////////////////////////
            inline CALname Program::getInputName(unsigned short i) const
            {
                assert(i <= _inputNames.size());
                return _inputNames[i];
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	i       The index of the constant register.
            //! \return	CALname The CAL name of the constant register.
            //!
            //! \brief	Get CAL name of a constant register.
            //!
            //////////////////////////////////////////////////////////////////////////
            inline CALname Program::getConstName(unsigned short i) const
            {
                assert(i <= _constNames.size());
                return _constNames[i];
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CALname The CAL name of the global register.
            //!
            //! \brief	Get CAL name of a global register.
            //!
            //////////////////////////////////////////////////////////////////////////
            inline CALname Program::getGlobalName() const
            {
                return _globalName;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \tparam Template type of the ProgramInfo, contains program parameter
            //!         information.
            //! \param	progInfo Instance of ProgramInfo, contains program ID and 
            //!         source
            //! \return	bool True if the Program object is successfully initialized.
            //!              False if the there is an error during initialization.
            //!
            //! \brief	Initialize the Program object. In this method, the IL source
            //!         provided in ProgramInfo will be compiled, linked and loaded 
            //!         onto CAL context of the device. Then, the module entry 
            //!         function handle and all the register names are retrieved.
            //!
            //////////////////////////////////////////////////////////////////////////
            template<typename ProgInfo>
            bool Program::initialize(const ProgInfo &progInfo)
            {
                if (!_device)
                {
                    return false;
                }

                CALdeviceinfo info = _device->getInfo();
                CALcontext ctx = _device->getContext();

                CALresult result;

                // Compiling program
                CALobject obj;
                result = calclCompile(&obj, CAL_LANGUAGE_IL, progInfo.getSource(), info.target);
                CHECK_CAL_RESULT_ERROR(result, "Failed to compile program\n");

                // Linking program
                CALimage image;
                result = calclLink(&image, &obj, 1);
                CHECK_CAL_RESULT_ERROR(result, "Failed to create image\n");
                calclFreeObject(obj);

                // Load program
                result = calModuleLoad(&_module, ctx, image);
                CHECK_CAL_RESULT_ERROR(result, "Failed to load module\n");
                calclFreeImage(image);

                // Get function handle
                result = calModuleGetEntry(&_func, ctx, _module, "main");
                CHECK_CAL_RESULT_ERROR(result, "Failed to get function handle\n");

                char symbolStr[16];
                // Get constant name handle
                for(unsigned int i = 0; i < ProgInfo::constants; ++i)
                {
                    CALname name = 0;
                    sprintf(symbolStr, "cb%d", i);
                    result = calModuleGetName(&name, ctx, _module, symbolStr);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to get name handle for constants\n");

                    _constNames.push_back(name);
                }

                
                // Get all the input name handles
                for(unsigned int i = 0; i < ProgInfo::inputs; ++i)
                {
                    CALname name = 0;
                    sprintf(symbolStr, "i%d", i);
                    result = calModuleGetName(&name, ctx, _module, symbolStr);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to get name handle for input stream\n");

                    _inputNames.push_back(name);
                }

                // Get all the output name handles
                for(unsigned int i = 0; i < ProgInfo::outputs; ++i)
                {
                    CALname name = 0;
                    sprintf(symbolStr, "o%d", i);
                    result = calModuleGetName(&name, ctx, _module, symbolStr);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to get name handle for output stream\n");

                    _outputNames.push_back(name);
                }

                // Get name handle for scatter stream
                if(ProgInfo::global != 0)
                {
                    CALname name = 0;
                    result = calModuleGetName(&name, ctx, _module, "g[]");
                    CHECK_CAL_RESULT_ERROR(result, "Failed to get name handle for global stream\n");

                    _globalName = name;
                }

                // Initialize Buffer
                _constBuffers.resize(ProgInfo::constants);
                _inputBuffers.resize(ProgInfo::inputs);
                _outputBuffers.resize(ProgInfo::outputs);
                _globalBuffer = BufferItem();

                return true;
            }
        }
    }
}

#endif //AMDSPL_PROGRAM_DEFS_H_
