#include "SplSort.h"
#include "SplBitonicSortImpl.h"
#include "cal.h"
#include "calcl.h"
#include "CALBuffer.h"
#include "CALDevice.h"
#include "CALConstBuffer.h"
#include "CALRuntime.h"
#include "CALBufferMgr.h"
#include "Sort_IL.h"
#include "CALProgram.h"
#include "CALBase.h"
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include "Timer.h"
#include <float.h>
#include "SplBitonicSortImpl.h"


namespace amdspl
{

#ifdef _AMDSPL_PERF_
    static CPerfCounter timer;
#endif // _AMDSPL_PERF_

    SplBitonicSortImpl::SplBitonicSortImpl(void)
    {
    }

    SplBitonicSortImpl::~SplBitonicSortImpl(void)
    {
    }

    bool SplBitonicSortImpl::bitonicSortImpl(float* ptr, unsigned int _size)
    {
        CALresult result = CAL_RESULT_OK;;
        unsigned int flip = 0;

        unsigned int _lgArraySize = 0;
        unsigned int _stage;

        uint bufferSize = bufferSize = utils::ceilPow(_size);
        for (; bufferSize >> _lgArraySize; _lgArraySize++)
        {
            ;
        }
        _lgArraySize--;

        CalBufferMgr* bufferMgr = CalRuntime::getInstance()->getBufferMgr();
        CalDevice* device = CalRuntime::getInstance()->getDevice();
        CALcontext ctx = device->getContext();

        uint InputDim[] = {bufferSize};
        CalBuffer *sorted1Buffer = CalBuffer::createBuffer(1, InputDim, CAL_FORMAT_FLOAT_1);
        CalBuffer *sorted2Buffer = CalBuffer::createBuffer(1, InputDim, CAL_FORMAT_FLOAT_1);

        if ( bufferSize != _size)
        {
            //When the buffer size is smaller than the real size, initiallization is needed.
            CalProgram<ILParaByID<SORT_ILPARA_LIST, BITONIC_INIT_IL>::Result> *program = 
                CalProgram<ILParaByID<SORT_ILPARA_LIST, BITONIC_INIT_IL>::Result>::getInstance();
            CalConstBuffer<1> *constBuffer = program->getConstantBuffer();
            const float minFloat = FLT_MAX;
            constBuffer->setConstant<0>(&minFloat);

            CALname outputName = program->getOutputName(0);
            CALmem mem = sorted1Buffer->getMemHandle();

            result = calCtxSetMem(ctx, outputName, mem);
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

            CALdomain rect = {0, 0, bufferSize, 1};
            program->executeProgram(rect);
            program->waitDoneEvent();
            program->cleanup();
        }

        CalProgram<ILParaByID<SORT_ILPARA_LIST, BITONIC_SORT_IL>::Result> *program = 
            CalProgram<ILParaByID<SORT_ILPARA_LIST, BITONIC_SORT_IL>::Result>::getInstance();
        CalConstBuffer<3> *constBuffer = program->getConstantBuffer();

#ifdef _AMDSPL_PERF_
        timer.Reset();
        timer.Start();
#endif // _AMDSPL_PERF_

        sorted1Buffer->readData(ptr, _size);

#ifdef _AMDSPL_PERF_
        timer.Stop();
        std::cout << "Data Read Time: " << timer.GetElapsedTime() << std::endl;
#endif // _AMDSPL_PERF_

        CALname inputName = program->getInputName(0);
        CALname outputName = program->getOutputName(0);
        CALmem mem1 = sorted1Buffer->getMemHandle();
        CALmem mem2 = sorted2Buffer->getMemHandle();

        CALname constName = program->getConstName();
        CALmem constMem = constBuffer->getMemHandle();

        result = calCtxSetMem(ctx, constName, constMem);
        AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind constant resource\n");

        CALdomain rect = {0, 0, bufferSize, 1};

#ifdef _AMDSPL_PERF_
        timer.Reset();
        timer.Start();
#endif // _AMDSPL_PERF_

        for(_stage = 1; _stage <= _lgArraySize; _stage++)
        {
            unsigned int step = 0;
            // Width of each sorted segment to be sorted in parallel (2, 4, 8, ...)
            unsigned int segWidth = 1 << _stage;

            for (step = 1; step <= _stage; ++step)
            {
                // offset = (stageWidth/2, stageWidth/4, ... , 2, 1)
                unsigned int offset = 1 << (_stage - step);
                unsigned int offset_2 = offset << 1;

                if (!flip)
                {
                    result = calCtxSetMem(ctx, inputName, mem1);
                    AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");
                    result = calCtxSetMem(ctx, outputName, mem2);
                    AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

                    constBuffer->setConstant<0>(&segWidth);
                    constBuffer->setConstant<1>(&offset);
                    constBuffer->setConstant<2>(&offset_2);

                    // Run the kernel on GPU
                    program->executeProgram(rect);
                    program->waitDoneEvent();
                }
                else
                {
                    result = calCtxSetMem(ctx, inputName, mem2);
                    AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");
                    result = calCtxSetMem(ctx, outputName, mem1);
                    AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

                    constBuffer->setConstant<0>(&segWidth);
                    constBuffer->setConstant<1>(&offset);
                    constBuffer->setConstant<2>(&offset_2);

                    // Run the kernel on GPU
                    program->executeProgram(rect);
                    program->waitDoneEvent();
                }

                flip ^= 0x01; // XOR flip w/ 0b1 which flips the flip variable between 0 and 1
            }
        }
#ifdef _AMDSPL_PERF_
        timer.Stop();
        std::cout << "Computing Time: " << timer.GetElapsedTime() << std::endl;
        timer.Reset();
        timer.Start();
#endif // _AMDSPL_PERF_
        if (!flip)
        {
            sorted1Buffer->writeData(ptr, _size);
        }
        else
        {
            sorted2Buffer->writeData(ptr, _size);
        }
#ifdef _AMDSPL_PERF_
        timer.Stop();
        std::cout << "Data Write time: " << timer.GetElapsedTime() << std::endl;
#endif // _AMDSPL_PERF_

        //CalBuffer::destroyBuffer(constBuffer);
        CalBuffer::destroyBuffer(sorted1Buffer);
        CalBuffer::destroyBuffer(sorted2Buffer);
        return true;
    }


    //////////////////////////////////////////////////////////////////////////
    //!                                                                     
    //! \brief bitonicSort with address translation.
    //!
    //////////////////////////////////////////////////////////////////////////
    bool SplBitonicSortImpl::bitioncSortATImpl(float* ptr, unsigned int _size)
    {
        CALresult result = CAL_RESULT_OK;;

        unsigned int flip = 0;

        unsigned int _lgArraySize = 0;
        unsigned int _stage;

        uint bufferSize = bufferSize = utils::ceilPow(_size);
        for (; bufferSize >> _lgArraySize; _lgArraySize++)
        {
            ;
        }
        _lgArraySize--;


        CalBufferMgr* bufferMgr = CalRuntime::getInstance()->getBufferMgr();
        CalDevice* device = CalRuntime::getInstance()->getDevice();
        CALcontext ctx = device->getContext();
        CALdeviceinfo info = device->getInfo();

        unsigned int _width = info.maxResource1DWidth;
        unsigned int _height = static_cast<unsigned int>(ceil(static_cast<double>(bufferSize) / _width));
        if (_height > info.maxResource2DHeight)
        {
            return false;
        }

        uint InputDim[] = {_width, _height};
        CalBuffer *sorted1Buffer = CalBuffer::createBuffer(2, InputDim, CAL_FORMAT_FLOAT_1);
        CalBuffer *sorted2Buffer = CalBuffer::createBuffer(2, InputDim, CAL_FORMAT_FLOAT_1);

        if ( bufferSize != _size)
        {
            //When the buffer size is smaller than the real size, initiallization is needed.
            CalProgram<ILParaByID<SORT_ILPARA_LIST, BITONIC_INIT_IL>::Result> *program = 
                CalProgram<ILParaByID<SORT_ILPARA_LIST, BITONIC_INIT_IL>::Result>::getInstance();
            CalConstBuffer<1> *constBuffer = program->getConstantBuffer();
            const float minFloat = FLT_MAX;
            constBuffer->setConstant<0>(&minFloat);

            CALname outputName = program->getOutputName(0);
            CALmem mem = sorted1Buffer->getMemHandle();

            result = calCtxSetMem(ctx, outputName, mem);
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

            CALdomain rect = {0, 0, _width, _height};
            program->executeProgram(rect);
            program->waitDoneEvent();
            program->cleanup();
        }

        CalProgram<ILParaByID<SORT_ILPARA_LIST, BITONIC_SORT_AT_IL>::Result> *program = 
            CalProgram<ILParaByID<SORT_ILPARA_LIST, BITONIC_SORT_AT_IL>::Result>::getInstance();

        CalConstBuffer<4> *constBuffer = program->getConstantBuffer();

        uint4 bufferDim;
        bufferDim.x = _width;
        bufferDim.y = _height;

        constBuffer->setConstant<3>(&bufferDim);

#ifdef _AMDSPL_PERF_
        timer.Reset();
        timer.Start();
#endif // _AMDSPL_PERF_

        sorted1Buffer->readData(ptr, _size);

#ifdef _AMDSPL_PERF_
        timer.Stop();
        std::cout << "Data Read Time: " << timer.GetElapsedTime() << std::endl;
#endif // _AMDSPL_PERF_

        CALname inputName = program->getInputName(0);
        CALname outputName = program->getOutputName(0);
        CALmem mem1 = sorted1Buffer->getMemHandle();
        CALmem mem2 = sorted2Buffer->getMemHandle();
        CALname constName = program->getConstName();
        CALmem constMem = constBuffer->getMemHandle();

        result = calCtxSetMem(ctx, constName, constMem);
        AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind constant resource\n");

        CALdomain rect = {0, 0, _width, _height};

#ifdef _AMDSPL_PERF_
        timer.Reset();
        timer.Start();
#endif // _AMDSPL_PERF_

        for(_stage = 1; _stage <= _lgArraySize; _stage++)
        {
            unsigned int step = 0;
            // Width of each sorted segment to be sorted in parallel (2, 4, 8, ...)
            unsigned int segWidth = 1 << _stage;

            for (step = 1; step <= _stage; ++step)
            {
                // offset = (stageWidth/2, stageWidth/4, ... , 2, 1)
                unsigned int offset = 1 << (_stage - step);
                unsigned int offset_2 = offset << 1;

                if (!flip)
                {
                    result = calCtxSetMem(ctx, inputName, mem1);
                    AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");
                    result = calCtxSetMem(ctx, outputName, mem2);
                    AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

                    constBuffer->setConstant<0>(&segWidth);
                    constBuffer->setConstant<1>(&offset);
                    constBuffer->setConstant<2>(&offset_2);

                    // Run the kernel on GPU
                    program->executeProgram(rect);
                    program->waitDoneEvent();
                }
                else
                {
                    result = calCtxSetMem(ctx, inputName, mem2);
                    AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");
                    result = calCtxSetMem(ctx, outputName, mem1);
                    AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

                    constBuffer->setConstant<0>(&segWidth);
                    constBuffer->setConstant<1>(&offset);
                    constBuffer->setConstant<2>(&offset_2);

                    // Run the kernel on GPU
                    program->executeProgram(rect);
                    program->waitDoneEvent();
                }

                flip ^= 0x01; // XOR flip w/ 0b1 which flips the flip variable between 0 and 1
            }
        }

#ifdef _AMDSPL_PERF_
        timer.Stop();
        std::cout << "Computing Time: " << timer.GetElapsedTime() << std::endl;
        timer.Reset();
        timer.Start();
#endif // _AMDSPL_PERF_

        if (!flip)
        {
            sorted1Buffer->writeData(ptr, _size);
        }
        else
        {
            sorted2Buffer->writeData(ptr, _size);
        }

#ifdef _AMDSPL_PERF_
        timer.Stop();
        std::cout << "Data Write time: " << timer.GetElapsedTime() << std::endl;
#endif // _AMDSPL_PERF_

        //CalBuffer::destroyBuffer(constBuffer);
        CalBuffer::destroyBuffer(sorted1Buffer);
        CalBuffer::destroyBuffer(sorted2Buffer);
        return true;
    }
}
