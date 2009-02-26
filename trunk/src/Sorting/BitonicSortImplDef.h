#ifndef _AMDSPL_BITONICSORT_IMPL_DEF_
#define _AMDSPL_BITONICSORT_IMPL_DEF_
#include <assert.h>
#include "RuntimeDefs.h"
#include <algorithm>

using namespace amdspl::core::cal;

namespace amdspl
{
    namespace sorting
    {
        //////////////////////////////////////////////////////////////////////////
        //! \brief Define IL grouping
        template<typename T>
        struct bitonic_sort_il_group;

        template<>
        struct bitonic_sort_il_group<float>
        {
        };

        template<>
        struct bitonic_sort_il_group<int>
        {
        };

        template<>
        struct bitonic_sort_il_group<unsigned int>
        {
        };

        template<>
        struct bitonic_sort_il_group<double>
        {
        };

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief The entrance point of the bitonic sort, 
        //!         seperate the implementation of AT and none-AT
        //!
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        bool BitonicSortImpl::sort(T *ptr, unsigned int size, bool asc)
        {
            if(!ptr || size == 0)
                return false;
            
            Device *device = Runtime::getInstance()->getDeviceManager()->getDefaultDevice();

            CALdeviceinfo info = device->getInfo();

            if (size <= info.maxResource1DWidth)
            {
                if (asc)
                {
                    std::sort(ptr, ptr + size, less<T>());
                }
                else
                    std::sort(ptr, ptr + size, greater<T>());
            }
            else
            {
                return BitonicSortImpl::sortAT(ptr, size, asc);
            }
        }

        //////////////////////////////////////////////////////////////////////////
        //!                                                                     
        //! \brief bitonicSort with address translation.
        //!
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        bool BitonicSortImpl::sortAT(T* ptr, unsigned int _size, bool asc)
        {
            CALresult result = CAL_RESULT_OK;;

            unsigned int flip = 0;

            CalBufferMgr* bufferMgr = CalRuntime::getInstance()->getBufferMgr();
            CalDevice* device = CalRuntime::getInstance()->getDevice();
            CALcontext ctx = device->getContext();
            CALdeviceinfo info = device->getInfo();


            if (_size > info.maxResource2DHeight * info.maxResource2DWidth)
            {
                return false; // too large to fix in vram
            }

            uint bufferSize = utils::ceilPow(_size);
            unsigned int _lgArraySize;
            for (_lgArraySize = 0; bufferSize >> _lgArraySize; _lgArraySize++)
            {
                ;
            }
            _lgArraySize--;

            unsigned int _width = info.maxResource1DWidth;
            unsigned int _height = static_cast<unsigned int>(ceil(static_cast<double>(bufferSize) / _width));

            uint dim[] = {_width, _height};
            CalBuffer *sorted1Buffer = CalBuffer::createBuffer(2, dim, utils::type_descriptor<T>::Format);
            CalBuffer *sorted2Buffer = CalBuffer::createBuffer(2, dim, utils::type_descriptor<T>::Format);

            assert(sorted1Buffer && sorted2Buffer);
            if (!sorted1Buffer || !sorted2Buffer)
            {
                return false;
            }

            if ( bufferSize != _size)
            {
                //When the buffer size is smaller than the real size, initialization is needed.
                CALdomain rect = {0, 0, _width, _height};
                result = InitialBuffer<T>(asc, sorted1Buffer, rect);
                AMDSPL_CAL_RESULT_ERROR(result, "Failed to initialize buffer\n")
            }

            CalProgram *program = asc ?
                CalProgram::getProgram<SORT_ILPARA_LIST, bitonic_sort_il_group<T>::AcsATId>() :
            CalProgram::getProgram<SORT_ILPARA_LIST, bitonic_sort_il_group<T>::DesATId>();

            CalConstBuffer<4> *constBuffer = CalConstBuffer<4>::createConstBuffer();

            uint bufferDim;
            bufferDim = _width;

            constBuffer->setConstant<3>(&bufferDim);
            sorted1Buffer->readData(ptr, _size);

            CALname inputName = program->getInputName(0);
            CALname outputName = program->getOutputName(0);

            CALmem mem1 = sorted1Buffer->getMemHandle();
            CALmem mem2 = sorted2Buffer->getMemHandle();

            CALname constName = program->getConstName();
            CALmem constMem = constBuffer->getMemHandle();

            result = calCtxSetMem(ctx, constName, constMem);
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind constant resource\n");

            CALdomain rect = {0, 0, _width, _height};

            unsigned int _stage;

            for(_stage = 1; _stage <= _lgArraySize; _stage++)
            {
                unsigned int step = 0;
                // Width of each sorted segment to be sorted in parallel (2, 4, 8, ...)

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

                        constBuffer->setConstant<0>(&_stage);
                        constBuffer->setConstant<1>(&offset);
                        constBuffer->setConstant<2>(&offset_2);
                        constBuffer->setDataToBuffer();

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

                        constBuffer->setConstant<0>(&_stage);
                        constBuffer->setConstant<1>(&offset);
                        constBuffer->setConstant<2>(&offset_2);
                        constBuffer->setDataToBuffer();

                        // Run the kernel on GPU
                        program->executeProgram(rect);
                        program->waitDoneEvent();
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

            SAFE_DELETE(program);
            return true;
        }
    }
}

#endif