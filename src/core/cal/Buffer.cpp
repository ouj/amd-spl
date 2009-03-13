//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		Buffer.cpp
//!	\date 		27:2:2009   22:19
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of Buffer class.
//!
//////////////////////////////////////////////////////////////////////////
#include "RuntimeDefs.h"
#include "CalCommonDefs.h"
#include <stdio.h>
#include "Utility.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	format Indicate the CALformat of the buffer.
            //! \param	width  Indicate the width of the 1D/2D buffer.
            //! \param	height  Indicate the height of 2D buffer, it should be set to
            //!         zero for 1D buffer.
            //! \return	Constructor
            //!
            //! \brief	Construct the Buffer object. Set all the members to default 
            //!         values. The Buffer object will not be available until 
            //!         Buffer::initialize() is called.
            //!
            //////////////////////////////////////////////////////////////////////////
            Buffer::Buffer(CALformat format, unsigned int width, unsigned int height) : 
                    _dataFormat(format), _width(width), _height(height), _res(0), _pitch(0),
                        _inputEvent(NULL), _outputEvent(NULL)
            {
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy the Buffer object, safely release the buffer's 
            //!         resource handle.
            //!
            //////////////////////////////////////////////////////////////////////////
            Buffer::~Buffer()
            {
                if(_res)
                {
                    calResFree(_res);
                    _res = 0;
                }
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	bool True if the buffer is initialized successful. False if
            //!         there is an error during initialization.
            //!
            //! \brief	Initialize the buffer before the buffer can be used, it is a 
            //!         virtual function, should be implemented by derived classes.
            //!
            //////////////////////////////////////////////////////////////////////////
            bool Buffer::initialize()
            {
                return true;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	ptr     The CPU address contains the data going to be transfered 
            //!                 to the buffer.
            //! \param	size    The size in bytes of the data  the pointer points to.
            //! \param	defaultVal  The default value should be set to the rest of the buffer.
            //! \return	bool    True if data transfer is succeeded. False if there is an error
            //!                 during data transfer.
            //!
            //! \brief	Transfer the data from CPU memory to the buffer(maybe LocalBuffer or 
            //!         RemoteBuffer). Sometimes the buffer is larger than the data that is 
            //!         going to be transfered. In this case, if defaulVal is set, the method 
            //!         will set the rest of buffer using the default value pointed by defaultVal.
            //!
            //! \attention It is the developers' responsibility to make sure the format and size 
            //!            of the CPU memory that ptr points to are valid.
            //!
            //////////////////////////////////////////////////////////////////////////
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

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	ptr     The CPU address where that data in buffer will be transfered to.
            //! \param	size    The size in bytes of the space the pointer points to.
            //! \return	bool    True if data transfer is succeeded. False if there is an error
            //!                 during data transfer.
            //!
            //! \brief	Transfer the data to CPU memory from the buffer(maybe LocalBuffer or 
            //!         RemoteBuffer). 
            //!
            //! \attention It is the developers' responsibility to make sure the format and size 
            //!            of the CPU memory that ptr points to are valid.
            //!
            //////////////////////////////////////////////////////////////////////////
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

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	e The input Event.
            //! \return	bool True if the input event is successfully set. False if the
            //!           the event is invalid.
            //!
            //! \brief	Set the input event of the buffer. Called when the buffer is used 
            //!         as a input buffer in a program.
            //!
            //////////////////////////////////////////////////////////////////////////
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

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	e The output Event.
            //! \return	bool True if the output event is successfully set. False if the
            //!           the event is invalid.
            //!
            //! \brief	Set the output event of the buffer. Called when the buffer is used
            //!         as a output buffer in a program.
            //!
            //////////////////////////////////////////////////////////////////////////
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

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	void
            //!
            //! \brief	Wait for the input event to complete. Usually called before
            //!         using this buffer as an output buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            void Buffer::waitInputEvent()
            {
                if (!_inputEvent)
                    return;
                else
                {
                    _inputEvent->waitEvent();
                }
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	void
            //!
            //! \brief	Wait for the output event to complete. Usually called before
            //!         using this buffer as an input buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            void Buffer::waitOutputEvent()
            {
                if (!_outputEvent)
                    return;
                else
                {
                    _outputEvent->waitEvent();
                }
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CALresource
            //!
            //! \brief	Get the CAL resouce handle of the buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            CALresource Buffer::getResHandle()
            {
                return _res;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	CALformat
            //!
            //! \brief	Get the CAL format of the buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            CALformat Buffer::getFormat()
            {
                return _dataFormat;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	unsigned int
            //!
            //! \brief	Get the pitch of the buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            unsigned int Buffer::getPitch()
            {
                if(!_pitch)
                {
                    getPointerCPU(_pitch);
                    releasePointerCPU();
                }
                return _pitch;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	unsigned int
            //!
            //! \brief	Get the width of the buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            unsigned int Buffer::getWidth()
            {
                return _width;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	unsigned int
            //!
            //! \brief	Get the height of the buffer, return 0 if it is a 1D buffer.
            //!
            //////////////////////////////////////////////////////////////////////////
            unsigned int Buffer::getHeight()
            {
                return _height;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param[out]	pitch The pitch of the buffer will be set.
            //! \return	void*     Return address of mapped memeory.
            //!
            //! \brief	Maps Buffer to a CPU addressable pointer
            //!
            //////////////////////////////////////////////////////////////////////////
            void* Buffer::getPointerCPU(CALuint &pitch)
            {
                void* bufferPtr;
                CALresult result = calResMap(&bufferPtr, &pitch,
                    _res, 0);

                CHECK_CAL_RESULT_ERROR2(result, "Failed to get CPU pointer\n");
                return bufferPtr;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	void
            //!
            //! \brief	Frees mapped memory
            //!
            //////////////////////////////////////////////////////////////////////////
            void Buffer::releasePointerCPU()
            {
                CALresult result = calResUnmap(_res);
                LOG_CAL_RESULT_ERROR(result, "Failed to unmap resource\n");
            }

        }
    }
}
