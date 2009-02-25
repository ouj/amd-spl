//
//
//
//  @ Project : AMD-SPL
//  @ File Name : Buffer.cpp
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#include "Buffer.h"
#include "RuntimeDefs.h"
#include <stdio.h>
#include "Utility.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            Buffer::Buffer(CALformat format, unsigned int width, unsigned int height) : 
                    _dataFormat(format), _width(width), _height(height), _res(0), _pitch(0),
                        _inputEvent(NULL), _outputEvent(NULL)
            {
            }

            Buffer::~Buffer()
            {
                if(_res)
                    calResFree(_res);
            }

            bool Buffer::initialize()
            {
                return true;
            }

            bool Buffer::readData(void *ptr, unsigned long size, void *defaultVal)
            {
                char *cpuPtr = static_cast<char*>(ptr);
                if (!cpuPtr)
                {
                    return false;
                }

                waitInputEvent();

                CALuint pitch;
                char* gpuPtr = static_cast<char*>(getPointerCPU(pitch));
                if (!gpuPtr)
                {
                    return false;
                }

                // element size
                unsigned short elementStride = utils::getElementBytes(_dataFormat);

                //bytes in the gpu buffer
                unsigned int height = _height == 0 ? 1 : _height; //1D

                unsigned int bufferBytes = 
                    elementStride *  _width * height;

                //bytes in the cpu buffer
                unsigned int totalBytes = size * elementStride;

                if (bufferBytes < totalBytes)
                {
                    return false;
                }

                //bytes that should set the default value
                unsigned int defaultBytes = bufferBytes - totalBytes;
                
                unsigned int cpuRowStride = elementStride * _width;
                unsigned int gpuRowStride = elementStride * pitch;

                if (cpuRowStride == gpuRowStride)
                {
                    memcpy(gpuPtr, cpuPtr, totalBytes);
                    if (defaultBytes && defaultVal)
                    {
                        gpuPtr += totalBytes;
                        while (defaultBytes)
                        {
                            memcpy(gpuPtr, defaultVal, elementStride);
                            gpuPtr += elementStride;
                            defaultBytes -= elementStride;
                        }
                    }
                }
                else
                {
                    unsigned int bytesCopied = 0;
                    for (unsigned int row = 0; row < height - 1; row++)
                    {
                        memcpy(gpuPtr, cpuPtr, cpuRowStride);
                        gpuPtr += gpuRowStride;
                        cpuPtr += cpuRowStride;
                    }

                    unsigned int remainBytes = totalBytes - (cpuPtr - static_cast<char*>(ptr));
                    if (remainBytes)
                    {
                        memcpy(gpuPtr, cpuPtr, remainBytes);
                    }

                    if (defaultBytes && defaultVal)
                    {
                        char* tmpPtr = gpuPtr + remainBytes;
                        unsigned int remainBytesInRow = cpuRowStride - remainBytes;
                        while (defaultBytes)
                        {
                            if (remainBytesInRow == 0)
                            {
                                remainBytesInRow = cpuRowStride;
                                gpuPtr += gpuRowStride;
                                tmpPtr = gpuPtr;
                            }
                            memcpy(tmpPtr, defaultVal, elementStride);
                            tmpPtr += elementStride;
                            remainBytesInRow -= elementStride;
                            defaultBytes -= elementStride;
                        }
                    }
                }
                releasePointerCPU();
                return true;
            }

            bool Buffer::writeData(void *ptr, unsigned long size)
            {
                char *cpuPtr = static_cast<char*>(ptr);
                if (!cpuPtr)
                {
                    return false;
                }

                waitOutputEvent();

                CALuint pitch;
                char* gpuPtr = static_cast<char*>(getPointerCPU(pitch));
                if (!gpuPtr)
                {
                    return false;
                }

                // element size
                unsigned short elementStride = utils::getElementBytes(_dataFormat);

                //bytes in the gpu buffer
                unsigned int height = _height == 0 ? 1 : _height; //1D

                unsigned int bufferBytes = 
                    elementStride *  _width * height;

                //bytes in the cpu buffer
                unsigned int totalBytes = size * elementStride;

                if (totalBytes < bufferBytes)
                {
                    return false;
                }

                unsigned int cpuRowStride = elementStride * _width;
                unsigned int gpuRowStride = elementStride * pitch;

                if (cpuRowStride == gpuRowStride)
                {
                    memcpy(cpuPtr, gpuPtr, totalBytes);
                }
                else
                {
                    for (unsigned int row = 0; row < height - 1; row++)
                    {
                        memcpy(cpuPtr, gpuPtr, cpuRowStride);
                        gpuPtr += gpuRowStride;
                        cpuPtr += cpuRowStride;
                    }
                    unsigned int remainBytes = totalBytes - (cpuPtr - static_cast<char*>(ptr));
                    if (remainBytes)
                    {
                        memcpy(cpuPtr, gpuPtr, remainBytes);
                    }
                }
                releasePointerCPU();
                return true;
            }

            bool Buffer::setInputEvent(Event* e)
            {
                if (!e)
                    return false;
                if (!e->isUnused())
                {
                    _inputEvent = e;
                    return true;
                }
                else
                    return false;
            }

            bool Buffer::setOutputEvent(Event* e)
            {
                if (!e)
                    return false;
                if (!e->isUnused())
                {
                    _outputEvent = e;
                    return true;
                }
                else
                    return false;
            }

            void Buffer::waitInputEvent()
            {
                if (!_inputEvent)
                    return;
                else
                {
                    _inputEvent->waitEvent();
                }
            }

            void Buffer::waitOutputEvent()
            {
                if (!_outputEvent)
                    return;
                else
                {
                    _outputEvent->waitEvent();
                }
            }

            CALresource Buffer::getResHandle()
            {
                return _res;
            }

            CALformat Buffer::getFormat()
            {
                return _dataFormat;
            }

            unsigned int Buffer::getPitch()
            {
                if(!_pitch)
                {
                    getPointerCPU(_pitch);
                    releasePointerCPU();
                }
                return _pitch;
            }

            unsigned int Buffer::getWidth()
            {
                return _width;
            }

            unsigned int Buffer::getHeight()
            {
                return _height;
            }

            void* Buffer::getPointerCPU(CALuint &pitch)
            {
                void* bufferPtr;
                CALresult result = calResMap(&bufferPtr, &pitch,
                    _res, 0);

                if (CAL_RESULT_OK != result)
                {
                    LOG_ERROR("Failed to get CPU pointer\n");
                    return NULL;
                }
                return bufferPtr;
            }

            void Buffer::releasePointerCPU()
            {
                CALresult result = calResUnmap(_res);
                LOG_CAL_RESULT_ERROR(result, "Failed to unmap resource\n");
            }

        }
    }
}
