#include "SplSort.h"
#include "cal.h"
#include "calcl.h"
#include "CALBuffer.h"
#include "CALDevice.h"
#include "CALConstBuffer.h"
#include "CALRuntime.h"
#include "CALBufferMgr.h"
#include "CALProgramMgr.h"
#include "CALProgram.h"
#include "ILPrograms.h"
#include "CALBase.h"
#include <vector>
#include <cmath>

namespace amdspl
{
    void SPLSort::bitonicSort(float *ptr, unsigned int _size)
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
        CalBuffer *sorted1Buffer = bufferMgr->createBuffer(1, InputDim, CAL_FORMAT_FLOAT_1);
        CalBuffer *sorted2Buffer = bufferMgr->createBuffer(1, InputDim, CAL_FORMAT_FLOAT_1);
        CalConstBuffer *constBuffer = bufferMgr->createConstBuffer(3, CAL_FORMAT_FLOAT_1);

        const CalProgram *program = amdspl::CalRuntime::getInstance()->getProgramMgr()->GetProgram(BITONIC_SORT_IL);

        sorted1Buffer->readData(ptr);

        CALname inputName = program->getInputName(0);
        CALname outputName = program->getOutputName(0);
        CALmem mem1 = sorted1Buffer->getMemHandle();
        CALmem mem2 = sorted2Buffer->getMemHandle();

        CALname constName = program->getConstName(0);
        CALmem constMem = constBuffer->getMemHandle();

        result = calCtxSetMem(ctx, inputName, mem1);
        AMDSPL_CAL_RESULT_LOG(result, "Failed to bind input resource\n");

        result = calCtxSetMem(ctx, constName, constMem);
        AMDSPL_CAL_RESULT_LOG(result, "Failed to bind constant resource\n");

        result = calCtxSetMem(ctx, outputName, mem2);
        AMDSPL_CAL_RESULT_LOG(result, "Failed to bind input resource\n");

        CALevent execEvent;

        // Run the kernel on GPU
        CALfunc func = program->getFunction();
        CALdomain rect = {0, 0, _size, 1};

        std::vector<float> temp(_size);

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
                    AMDSPL_CAL_RESULT_LOG(result, "Failed to bind input resource\n");
                    result = calCtxSetMem(ctx, outputName, mem2);
                    AMDSPL_CAL_RESULT_LOG(result, "Failed to bind input resource\n");

                    constBuffer->setConstant(&segWidth, CAL_FORMAT_FLOAT_1, 0);
                    constBuffer->setConstant(&offset, CAL_FORMAT_FLOAT_1, 1);
                    constBuffer->setConstant(&offset_2, CAL_FORMAT_FLOAT_1, 2);
                    constBuffer->setDataToBuffer();

                    // Run the kernel on GPU
                    result = calCtxRunProgram(&execEvent, ctx, func, &rect);
                    //while(calCtxIsEventDone(ctx, execEvent));
                    
                }
                else
                {
                    result = calCtxSetMem(ctx, inputName, mem2);
                    AMDSPL_CAL_RESULT_LOG(result, "Failed to bind input resource\n");
                    result = calCtxSetMem(ctx, outputName, mem1);
                    AMDSPL_CAL_RESULT_LOG(result, "Failed to bind input resource\n");

                    constBuffer->setConstant(&segWidth, CAL_FORMAT_FLOAT_1, 0);
                    constBuffer->setConstant(&offset, CAL_FORMAT_FLOAT_1, 1);
                    constBuffer->setConstant(&offset_2, CAL_FORMAT_FLOAT_1, 2);
                    constBuffer->setDataToBuffer();

                    // Run the kernel on GPU
                    result = calCtxRunProgram(&execEvent, ctx, func, &rect);
                    //while(calCtxIsEventDone(ctx, execEvent));
                }
                flip ^= 0x01; // XOR flip w/ 0b1 which flips the flip variable between 0 and 1
            }
        }

        if (flip)
        {
            sorted1Buffer->writeData(ptr);
        }
        else
        {
            sorted2Buffer->writeData(ptr);
        }

        bufferMgr->destroyBuffer(sorted1Buffer);
        bufferMgr->destroyBuffer(sorted2Buffer);
    }

}
