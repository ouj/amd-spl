#ifndef _AMDSPL_BITONICSORT_IMPL_
#define _AMDSPL_BITONICSORT_IMPL_

#include "SplBitonicSort.h"
#include "Sort_IL.h"
#include "Utility.h"
#include "CALProgram.h"
#include "CALBase.h"
#include <cmath>

namespace amdspl
{
    namespace sorting
    {

        template<typename T>
        struct bitonic_sort_il_id;

        template<>
        struct bitonic_sort_il_id<float>
        {
            enum{ 
                AcsId = BITONIC_SORT_FLOAT_ACS_IL, 
                DesId = BITONIC_SORT_FLOAT_DES_IL, 
                AcsATId = BITONIC_SORT_FLOAT_ACS_AT_IL, 
                DesATId = BITONIC_SORT_FLOAT_DES_AT_IL
            };
        };

        template<>
        struct bitonic_sort_il_id<int>
        {
            enum{ 
                AcsId = BITONIC_SORT_INT_ACS_IL, 
                DesId = BITONIC_SORT_INT_DES_IL, 
                AcsATId = BITONIC_SORT_INT_ACS_AT_IL, 
                DesATId = BITONIC_SORT_INT_DES_AT_IL
            };
        };

        class BitonicSortImpl : public BitonicSort
        {
        private:
            BitonicSortImpl(void) {};
            ~BitonicSortImpl(void) {};
        public:
            template<class T>
            static bool bitonicSortImpl(T* ptr, unsigned int _size, bool asc);
            template<class T>
            static bool bitioncSortATImpl(T* ptr, unsigned int _size, bool asc);
        };

        //////////////////////////////////////////////////////////////////////////
        //!                                                                     
        //! \brief bitonicSort without address translation.
        //!
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        bool BitonicSortImpl::bitonicSortImpl(T* ptr, unsigned int _size, bool asc)
        {
            CALresult result = CAL_RESULT_OK;;
            unsigned int flip = 0;

            unsigned int _lgArraySize = 0;

            uint bufferSize = utils::ceilPow(_size);
            for (; bufferSize >> _lgArraySize; _lgArraySize++){;}
            _lgArraySize--;

            CalBufferMgr* bufferMgr = CalRuntime::getInstance()->getBufferMgr();
            CalDevice* device = CalRuntime::getInstance()->getDevice();
            CALcontext ctx = device->getContext();

            uint InputDim[] = {bufferSize};
            CalBuffer *sorted1Buffer = CalBuffer::createBuffer(1, InputDim, utils::type_descriptor<T>::Format);
            CalBuffer *sorted2Buffer = CalBuffer::createBuffer(1, InputDim, utils::type_descriptor<T>::Format);

            if ( bufferSize != _size)
            {
                //When the buffer size is smaller than the real size, initialization is needed.
                CalProgram *program = 
                    CalProgram::getProgram<SORT_ILPARA_LIST, BITONIC_INIT_IL>();
                CalConstBuffer<1> *constBuffer = CalConstBuffer<1>::createConstBuffer();
                const T extremeValue = asc ? utils::extreme_value<T>::MaxValue : utils::extreme_value<T>::MinValue;
                constBuffer->setConstant<0>(&extremeValue);
                constBuffer->setDataToBuffer();

                CALname constName = program->getConstName();
                CALmem constMem = constBuffer->getMemHandle();

                result = calCtxSetMem(ctx, constName, constMem);
                AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind constants\n");

                CALname outputName = program->getOutputName(0);
                CALmem mem = sorted1Buffer->getMemHandle();

                result = calCtxSetMem(ctx, outputName, mem);
                AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind output resource\n");

                CALdomain rect = {0, 0, bufferSize, 1};
                program->executeProgram(rect);
                program->waitDoneEvent();

                CalConstBuffer<1>::destroyBuffer(constBuffer);
                SAFE_DELETE(program);
            }

            CalProgram *program = asc ? 
                CalProgram::getProgram<SORT_ILPARA_LIST, bitonic_sort_il_id<T>::AcsId>() :
                CalProgram::getProgram<SORT_ILPARA_LIST, bitonic_sort_il_id<T>::DesId>();

            CalConstBuffer<3> *constBuffer = CalConstBuffer<3>::createConstBuffer();

            sorted1Buffer->readData(ptr, _size);

            CALname inputName = program->getInputName(0);
            CALname outputName = program->getOutputName(0);
            CALmem mem1 = sorted1Buffer->getMemHandle();
            CALmem mem2 = sorted2Buffer->getMemHandle();

            CALname constName = program->getConstName();
            CALmem constMem = constBuffer->getMemHandle();

            result = calCtxSetMem(ctx, constName, constMem);
            AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind constant resource\n");

            CALdomain rect = {0, 0, bufferSize, 1};

            // Width of each sorted segment to be sorted in parallel (2, 4, 8, ...)
            unsigned int _stage;
            for(_stage = 1; _stage <= _lgArraySize; _stage++)
            {
                unsigned int step = 0;

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
                sorted1Buffer->writeData(ptr, _size);
            else
                sorted2Buffer->writeData(ptr, _size);

            CalBuffer::destroyBuffer(constBuffer);
            CalBuffer::destroyBuffer(sorted1Buffer);
            CalBuffer::destroyBuffer(sorted2Buffer);

            SAFE_DELETE(program);
            return true;
        }

        //////////////////////////////////////////////////////////////////////////
        //!                                                                     
        //! \brief bitonicSort with address translation.
        //!
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        bool BitonicSortImpl::bitioncSortATImpl(T* ptr, unsigned int _size, bool asc)
        {
            CALresult result = CAL_RESULT_OK;;

            unsigned int flip = 0;

            unsigned int _lgArraySize;

            uint bufferSize = utils::ceilPow(_size);
            for (_lgArraySize = 0; bufferSize >> _lgArraySize; _lgArraySize++)
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
            CalBuffer *sorted1Buffer = CalBuffer::createBuffer(2, InputDim, utils::type_descriptor<T>::Format);
            CalBuffer *sorted2Buffer = CalBuffer::createBuffer(2, InputDim, utils::type_descriptor<T>::Format);

            if ( bufferSize != _size)
            {
                //When the buffer size is smaller than the real size, initialization is needed.
                CalProgram *program = 
                    CalProgram::getProgram<SORT_ILPARA_LIST, BITONIC_INIT_IL>();
                CalConstBuffer<1> *constBuffer = CalConstBuffer<1>::createConstBuffer();
                const T extremeValue = asc ? utils::extreme_value<T>::MaxValue : utils::extreme_value<T>::MinValue;
                constBuffer->setConstant<0>(&extremeValue);
                constBuffer->setDataToBuffer();

                CALname constName = program->getConstName();
                CALmem constMem = constBuffer->getMemHandle();

                result = calCtxSetMem(ctx, constName, constMem);
                AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind constants\n");

                CALname outputName = program->getOutputName(0);
                CALmem mem = sorted1Buffer->getMemHandle();

                result = calCtxSetMem(ctx, outputName, mem);
                AMDSPL_CAL_RESULT_ERROR(result, "Failed to bind input resource\n");

                CALdomain rect = {0, 0, _width, _height};
                program->executeProgram(rect);
                program->waitDoneEvent();

                SAFE_DELETE(program);
            }

            CalProgram *program = asc ?
                CalProgram::getProgram<SORT_ILPARA_LIST, bitonic_sort_il_id<T>::AcsATId>() :
                CalProgram::getProgram<SORT_ILPARA_LIST, bitonic_sort_il_id<T>::DesATId>();

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

