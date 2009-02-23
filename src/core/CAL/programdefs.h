#ifndef _PROGRAM_DEFS_H_
#define _PROGRAM_DEFS_H_

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            template<typename ProgInfo>
            bool Program::initialize()
            {
                CALdeviceinfo info = _device->getInfo();
                CALcontext ctx = _device->getContext();

                CALresult result;

                // Compiling program
                CALobject obj;
                result = calclCompile(&obj, CAL_LANGUAGE_IL, ProgInfo::source, info.target);
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
                    CALname name;
                    sprintf(symbolStr, "cb%d", i);
                    result = calModuleGetName(&name, ctx, _module, symbolStr);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to get name handle for constants\n");

                    _constNames.push_back(name);
                }

                
                // Get all the input name handles
                for(unsigned int i = 0; i < ProgInfo::inputs; ++i)
                {
                    CALname name;
                    sprintf(symbolStr, "i%d", i);
                    result = calModuleGetName(&name, ctx, _module, symbolStr);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to get name handle for input stream\n");

                    _inputNames.push_back(name);
                }

                // Get all the output name handles
                for(unsigned int i = 0; i < ProgInfo::outputs; ++i)
                {
                    CALname name;
                    sprintf(symbolStr, "o%d", i);
                    result = calModuleGetName(&name, ctx, _module, symbolStr);
                    CHECK_CAL_RESULT_ERROR(result, "Failed to get name handle for output stream\n");

                    _outputNames.push_back(name);
                }

                // Get name handle for scatter stream
                if(ProgInfo::global != 0)
                {
                    CALname name;
                    result = calModuleGetName(&name, ctx, _module, "g[]");
                    CHECK_CAL_RESULT_ERROR(result, "Failed to get name handle for scatter stream\n");

                    _globalName = name;
                }

                // Initialize buffer pointers
                _constBuffers.resize(ProgInfo::constants, NULL);
                _inputBuffers.resize(ProgInfo::inputs, NULL);
                _outputBuffers.resize(ProgInfo::outputs, NULL);
                _globalBuffer = NULL;

                return true;
            }
        }
    }
}

#endif //_PROGRAM_DEFS_H_