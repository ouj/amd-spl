#include "SplSort.h"
#include "cal.h"
#include "calcl.h"
#include "CALBuffer.h"
#include "CALDevice.h"
#include "CALConstBuffer.h"
#include "CALRuntime.h"
#include "CALBufferMgr.h"
#include "CALProgram.h"
#include "ILPrograms.h"
#include "CALBase.h"
#include <vector>
#include <cmath>
#include <cassert>

#define PREINIT_PROGRAM(ID) {CalProgram<ID>* program = CalProgram<ID>::getInstance();\
    assert(program); if (!program) return false;}

namespace amdspl
{
    bool SPLSort::initModule(void)
    {
        PREINIT_PROGRAM(BITONIC_SORT_IL);
        PREINIT_PROGRAM(BITONIC_SORT_AT_IL);
        return true;
    }

    bool SPLSort::bitonicSort(float *ptr, unsigned int _size)
    {
		CalDevice* device = CalRuntime::getInstance()->getDevice();
		CALdeviceinfo info = device->getInfo();
		if (_size <= info.maxResource1DWidth)
		{
			return bitonicSortImpl(ptr, _size);
		}
		else
		{
			unsigned int width = 
				static_cast<unsigned int>(sqrt(static_cast<double>(_size)));
			if (width > info.maxResource1DWidth)
			{
				return false;
			}
			unsigned int height = 
				static_cast<unsigned int>(ceil(static_cast<double>(_size) / width));
			if (height > info.maxResource2DHeight)
			{
				return false;
			}
			return bitioncSortATImpl(ptr, _size, width, height);
		}
    }

	bool SPLSort::bitonicSortImpl(float* ptr, unsigned int _size)
	{
		CALresult result = CAL_RESULT_OK;;
		unsigned int flip = 0;

		unsigned int _lgArraySize = 0;
		unsigned int _stage;

		for (_stage = _size >> 1; _stage; _lgArraySize++)
		{
			_stage >>= 1;
		}

		CalBufferMgr* bufferMgr = CalRuntime::getInstance()->getBufferMgr();
		CalDevice* device = CalRuntime::getInstance()->getDevice();
		CALcontext ctx = device->getContext();

		uint InputDim[] = {_size};
		CalBuffer *sorted1Buffer = CalBuffer::createBuffer(1, InputDim, CAL_FORMAT_FLOAT_1);
		CalBuffer *sorted2Buffer = CalBuffer::createBuffer(1, InputDim, CAL_FORMAT_FLOAT_1);
		CalConstBuffer<3> *constBuffer = bufferMgr->createConstBuffer<3>();
        const CalProgram<BITONIC_SORT_IL> *program = CalProgram<BITONIC_SORT_IL>::getInstance();

		sorted1Buffer->readData(ptr);

		CALname inputName = program->getInputName(0);
		CALname outputName = program->getOutputName(0);
		CALmem mem1 = sorted1Buffer->getMemHandle();
		CALmem mem2 = sorted2Buffer->getMemHandle();

		CALname constName = program->getConstName();
		CALmem constMem = constBuffer->getMemHandle();

		result = calCtxSetMem(ctx, inputName, mem1);
		AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

		result = calCtxSetMem(ctx, constName, constMem);
		AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind constant resource\n");

		result = calCtxSetMem(ctx, outputName, mem2);
		AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

		CALevent execEvent;

		// Run the kernel on GPU
		CALfunc func = program->getFunction();
		CALdomain rect = {0, 0, _size, 1};

		for(_stage = 1; _stage <= _lgArraySize; _stage++)
		{
			unsigned int step = 0;
			// Width of each sorted segment to be sorted in parallel (2, 4, 8, ...)
			float segWidth = (float)pow(2.0f, (int)_stage);

			for (step = 1; step <= _stage; ++step)
			{
				// offset = (stageWidth/2, stageWidth/4, ... , 2, 1)
				float offset = (float)pow(2.0f, (int)(_stage - step));
				float offset_2 = offset * 2.0f;

				if (!flip)
				{
					result = calCtxSetMem(ctx, inputName, mem1);
					AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");
					result = calCtxSetMem(ctx, outputName, mem2);
					AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

					constBuffer->setConstant<0>(&segWidth, CAL_FORMAT_FLOAT_1);
					constBuffer->setConstant<1>(&offset, CAL_FORMAT_FLOAT_1);
					constBuffer->setConstant<2>(&offset_2, CAL_FORMAT_FLOAT_1);
					constBuffer->setDataToBuffer();

					// Run the kernel on GPU
					result = calCtxRunProgram(&execEvent, ctx, func, &rect);
					while(calCtxIsEventDone(ctx, execEvent));

				}
				else
				{
					result = calCtxSetMem(ctx, inputName, mem2);
					AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");
					result = calCtxSetMem(ctx, outputName, mem1);
					AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

					constBuffer->setConstant<0>(&segWidth, CAL_FORMAT_FLOAT_1);
					constBuffer->setConstant<1>(&offset, CAL_FORMAT_FLOAT_1);
					constBuffer->setConstant<2>(&offset_2, CAL_FORMAT_FLOAT_1);
					constBuffer->setDataToBuffer();

					// Run the kernel on GPU
					result = calCtxRunProgram(&execEvent, ctx, func, &rect);
					while(calCtxIsEventDone(ctx, execEvent));
				}
				flip ^= 0x01; // XOR flip w/ 0b1 which flips the flip variable between 0 and 1
			}
		}

		if (!flip)
		{
			sorted1Buffer->writeData(ptr);
		}
		else
		{
			sorted2Buffer->writeData(ptr);
		}

		CalBuffer::destroyBuffer(constBuffer);
		CalBuffer::destroyBuffer(sorted1Buffer);
		CalBuffer::destroyBuffer(sorted2Buffer);
		return true;
	}

	bool SPLSort::bitioncSortATImpl(float* ptr, unsigned int _size, unsigned int _width, unsigned int _height)
	{
		CALresult result = CAL_RESULT_OK;;

        unsigned int flip = 0;

        unsigned int _lgArraySize = 0;
        unsigned int _stage;

        for (_stage = _size >> 1; _stage; _lgArraySize++)
        {
            _stage >>= 1;
        }

		CalBufferMgr* bufferMgr = CalRuntime::getInstance()->getBufferMgr();
		CalDevice* device = CalRuntime::getInstance()->getDevice();
		CALcontext ctx = device->getContext();

		uint InputDim[] = {_width, _height};
		CalBuffer *sorted1Buffer = CalBuffer::createBuffer(2, InputDim, CAL_FORMAT_FLOAT_1);
		CalBuffer *sorted2Buffer = CalBuffer::createBuffer(2, InputDim, CAL_FORMAT_FLOAT_1);

		CalConstBuffer<7> *constBuffer = bufferMgr->createConstBuffer<7>();
        const CalProgram<BITONIC_SORT_AT_IL> *program = CalProgram<BITONIC_SORT_AT_IL>::getInstance();
        
        uint4 bufferDim;
        bufferDim.x = _width;
        bufferDim.y = _height;

        uint4 strDim;
        strDim.x = _size;
        strDim.y = 1;

        constBuffer->setConstant<0>(&strDim, CAL_FORMAT_INT_4);
        constBuffer->setConstant<1>(&bufferDim, CAL_FORMAT_INT_4);
        constBuffer->setConstant<5>(&strDim, CAL_FORMAT_INT_4);
        constBuffer->setConstant<6>(&bufferDim, CAL_FORMAT_INT_4);

		sorted1Buffer->readData(ptr, _size);

		CALname inputName = program->getInputName(0);
		CALname outputName = program->getOutputName(0);
		CALmem mem1 = sorted1Buffer->getMemHandle();
		CALmem mem2 = sorted2Buffer->getMemHandle();
		CALname constName = program->getConstName();
		CALmem constMem = constBuffer->getMemHandle();



		result = calCtxSetMem(ctx, inputName, mem1);
		AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

		result = calCtxSetMem(ctx, constName, constMem);
		AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind constant resource\n");

		result = calCtxSetMem(ctx, outputName, mem2);
		AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

		constBuffer->setDataToBuffer();

		CALevent execEvent;


        // Run the kernel on GPU
        CALfunc func = program->getFunction();
        CALdomain rect = {0, 0, _width, _height};

        for(_stage = 1; _stage <= _lgArraySize; _stage++)
        {
            unsigned int step = 0;
            // Width of each sorted segment to be sorted in parallel (2, 4, 8, ...)
            float segWidth = (float)pow(2.0f, (int)_stage);

            for (step = 1; step <= _stage; ++step)
            {
                // offset = (stageWidth/2, stageWidth/4, ... , 2, 1)
                float offset = (float)pow(2.0f, (int)(_stage - step));
                float offset_2 = offset * 2.0f;

                if (!flip)
                {
                    result = calCtxSetMem(ctx, inputName, mem1);
                    AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");
                    result = calCtxSetMem(ctx, outputName, mem2);
                    AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

                    constBuffer->setConstant<2>(&segWidth, CAL_FORMAT_FLOAT_1);
                    constBuffer->setConstant<3>(&offset, CAL_FORMAT_FLOAT_1);
                    constBuffer->setConstant<4>(&offset_2, CAL_FORMAT_FLOAT_1);
                    constBuffer->setDataToBuffer();

                    // Run the kernel on GPU
                    result = calCtxRunProgram(&execEvent, ctx, func, &rect);
                    while(calCtxIsEventDone(ctx, execEvent));

                }
                else
                {
                    result = calCtxSetMem(ctx, inputName, mem2);
                    AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");
                    result = calCtxSetMem(ctx, outputName, mem1);
                    AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

                    constBuffer->setConstant<2>(&segWidth, CAL_FORMAT_FLOAT_1);
                    constBuffer->setConstant<3>(&offset, CAL_FORMAT_FLOAT_1);
                    constBuffer->setConstant<4>(&offset_2, CAL_FORMAT_FLOAT_1);
                    constBuffer->setDataToBuffer();

                    // Run the kernel on GPU
                    result = calCtxRunProgram(&execEvent, ctx, func, &rect);
                    while(calCtxIsEventDone(ctx, execEvent));
                }
                flip ^= 0x01; // XOR flip w/ 0b1 which flips the flip variable between 0 and 1
            }
        }

        if (!flip)
        {
            sorted1Buffer->writeData(ptr, _size);
        }
        else
        {
            sorted2Buffer->writeData(ptr, _size);
        }

		CalBuffer::destroyBuffer(constBuffer);
		CalBuffer::destroyBuffer(sorted1Buffer);
		CalBuffer::destroyBuffer(sorted2Buffer);
		return true;
	}
}
