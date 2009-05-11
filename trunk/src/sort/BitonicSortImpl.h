#ifndef _AMDSPL_BITONICSORT_IMPL_
#define _AMDSPL_BITONICSORT_IMPL_

#include "SplDefs.h"
#include "Utility.h"
#include <cmath>
#include "RuntimeDefs.h"
#include <algorithm>

using namespace amdspl::core::cal;
namespace amdspl
{
    namespace sorting
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \tparam T Template type of the maximum/mininum values. 
        //!
        //! \brief Define the maximum/minimum values different types.
        //!
        //////////////////////////////////////////////////////////////////////////
        template<typename T>
        struct extreme_value
        {
            static const T MinValue;
            static const T MaxValue;
        };

        template<>
        const int extreme_value<int>::MinValue = -INT_MAX;
        template<>
        const int extreme_value<int>::MaxValue = INT_MAX;

        template<>
        const unsigned int extreme_value<unsigned int>::MinValue = 0;
        template<>
        const unsigned int extreme_value<unsigned int>::MaxValue = UINT_MAX;

        template<>
        const float extreme_value<float>::MinValue = -FLT_MAX;
        template<>
        const float extreme_value<float>::MaxValue = FLT_MAX;

        template<>
        const double extreme_value<double>::MinValue = -DBL_MAX;
        template<>
        const double extreme_value<double>::MaxValue = DBL_MAX;


        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief IL source string of Bitonic sort for types except double
        //!
        //////////////////////////////////////////////////////////////////////////
        static const char* _sz_bitonic_sort_prog_source_ = 
            "il_ps_2_0\n"
            "dcl_output_generic o0\n"
            "dcl_resource_id(0)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
            "dcl_input_position_interp(linear_noperspective) v0.xy__\n"
            "dcl_literal l0, 0xFFFFFFFF, 0x00000001, 0x00000000, 0xFFFFFFFF\n"
            "dcl_cb cb0[4]\n"
            "sample_resource(0)_sampler(0) r5, v0.xy00\n"
            "ftoi r1.xy__, v0.xy00\n"
            "imul r1._y__, r1.0y00, cb0[3].0x00\n"
            "iadd r1.x___, r1.y000, r1.x000\n"
            "iadd r3.x___, cb0[2].x000, l0.x000\n"
            "and r3.x___, r1.x000, r3.x000\n"
            "ilt r3.x___, r3.x000, cb0[1].x000\n"
            "cmov_logical r3.x___, r3.x000, l0.y000, l0.x000\n"
            "ishr r4.x___, r1.x000, cb0[0].x000\n"
            "and r4.x___, r4.x000, l0.y000\n"
            "ieq r4.x___, r4.x000, l0.z000\n"
            "cmov_logical r4.x___, r4.x000, l0.y000, l0.x000\n"
            "imul r2.x___, r3.x000, cb0[1].x000\n"
            "iadd r2.x___, r2.x000, r1.x000\n"
            "udiv r2._y__, r2.0x00, cb0[3].0x00\n"
            "imul r7.x___, r2.y000, cb0[3].x000_neg(x)\n"
            "iadd r2.x___, r2.x000, r7.x000\n"
            "itof r2, r2\n"
            "sample_resource(0)_sampler(0) r6, r2.xy00\n"
            "{SORT_OPERATOR} r7, r5, r6\n" // with token
            "cmov_logical r8, r7, r5, r6\n"
            "cmov_logical r9, r7, r6, r5\n"
            "ieq r10, r3.x000, r4.x000\n"
            "cmov_logical o0.x___, r10, r8, r9\n"
            "endmain\n"
            "end\n";

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \tparam T Template type of the Bitonic sort ProgramInfo. 
        //!
        //! \brief The Bitonic sort ProgramInfo for ascending/descending sort of 
        //!         specific type.
        //!
        //////////////////////////////////////////////////////////////////////////
        template<typename T>
        struct bitonicSortILGroup
        {
            static const ProgramInfo asc;
            static const ProgramInfo des;
        };

        template<>
        const ProgramInfo bitonicSortILGroup<float>::asc = 
            ProgramInfo("Float Ascend Bitonic Sort Program Info", _sz_bitonic_sort_prog_source_)
            .replaceTkn("{SORT_OPERATOR}", "lt").outputs(1).inputs(1).constants(1); //less than.
        template<>
        const ProgramInfo bitonicSortILGroup<float>::des = 
            ProgramInfo("Float Descend Bitonic Sort Program Info", _sz_bitonic_sort_prog_source_)
            .replaceTkn("{SORT_OPERATOR}", "ge").outputs(1).inputs(1).constants(1); //greater or equal.

        template<>
        const ProgramInfo bitonicSortILGroup<int>::asc = 
            ProgramInfo("Integer Ascend Bitonic Sort Program Info", _sz_bitonic_sort_prog_source_)
            .replaceTkn("{SORT_OPERATOR}", "ilt").outputs(1).inputs(1).constants(1); //less than.
        template<>
        const ProgramInfo bitonicSortILGroup<int>::des = 
            ProgramInfo("Integer Descend Bitonic Sort Program Info", _sz_bitonic_sort_prog_source_)
            .replaceTkn("{SORT_OPERATOR}", "ige").outputs(1).inputs(1).constants(1); //greater or equal.
        
        template<>
        const ProgramInfo bitonicSortILGroup<unsigned int>::asc = 
            ProgramInfo("Unsigned Integer Ascend Bitonic Sort Program Info", _sz_bitonic_sort_prog_source_)
            .replaceTkn("{SORT_OPERATOR}", "ult").outputs(1).inputs(1).constants(1); //less than.
        template<>
        const ProgramInfo bitonicSortILGroup<unsigned int>::des = 
            ProgramInfo("Unsigned Integer Descend Bitonic Sort Program Info", _sz_bitonic_sort_prog_source_)
            .replaceTkn("{SORT_OPERATOR}", "uge").outputs(1).inputs(1).constants(1); //greater or equal.

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief IL source string of Bitonic sort for double
        //!
        //////////////////////////////////////////////////////////////////////////
        static const char* _sz_bitonic_sort_prog_source_double_ = 
            "il_ps_2_0\n"
            "dcl_output_generic o0\n"
            "dcl_resource_id(0)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
            "dcl_input_position_interp(linear_noperspective) v0.xy__\n"
            "dcl_literal l0, 0xFFFFFFFF, 0x00000001, 0x00000000, 0xFFFFFFFF\n"
            "dcl_cb cb0[4]\n"
            "sample_resource(0)_sampler(0) r5, v0.xy00\n"
            "ftoi r1.xy__, v0.xy00\n"
            "imul r1._y__, r1.0y00, cb0[3].0x00\n"
            "iadd r1.x___, r1.y000, r1.x000\n"
            "iadd r3.x___, cb0[2].x000, l0.x000\n"
            "and r3.x___, r1.x000, r3.x000\n"
            "ilt r3.x___, r3.x000, cb0[1].x000\n"
            "cmov_logical r3.x___, r3.x000, l0.y000, l0.x000\n"
            "ishr r4.x___, r1.x000, cb0[0].x000\n"
            "and r4.x___, r4.x000, l0.y000\n"
            "ieq r4.x___, r4.x000, l0.z000\n"
            "cmov_logical r4.x___, r4.x000, l0.y000, l0.x000\n"
            "imul r2.x___, r3.x000, cb0[1].x000\n"
            "iadd r2.x___, r2.x000, r1.x000\n"
            "udiv r2._y__, r2.0x00, cb0[3].0x00\n"
            "imul r7.x___, r2.y000, cb0[3].x000_neg(x)\n"
            "iadd r2.x___, r2.x000, r7.x000\n"
            "itof r2, r2\n"
            "sample_resource(0)_sampler(0) r6, r2.xy00\n"
            "{SORT_OPERATOR} r7, r5, r6\n" // with token
            "cmov_logical r8.xy, r7, r5, r6\n"
            "cmov_logical r9.xy, r7, r6, r5\n"
            "ieq r10, r3.xx00, r4.xx00\n"
            "cmov_logical o0.xy__, r10, r8, r9\n"
            "endmain\n"
            "end\n";
            
        template<>
        const ProgramInfo bitonicSortILGroup<double>::asc = 
            ProgramInfo("Double Ascend Bitonic Sort Program Info", _sz_bitonic_sort_prog_source_double_)
            .replaceTkn("{SORT_OPERATOR}", "dlt").outputs(1).inputs(1).constants(1); //less than.
        template<>
        const ProgramInfo bitonicSortILGroup<double>::des = 
            ProgramInfo("Double Descend Bitonic Sort Program Info", _sz_bitonic_sort_prog_source_double_)
            .replaceTkn("{SORT_OPERATOR}", "dge").outputs(1).inputs(1).constants(1); //greater or equal.

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \tparam The type of sorting value.
        //!
        //! \param	ptr     The CPU address of the array to be sort.
        //! \param	size    The size of the array to be sort.
        //! \param	asc     Boolean value indicate whether to sort the array 
        //!                 in ascendant order or descendant order.
        //! \return	SPL_RESULT  
        //!                 SPL_RESULT_OK - if the array is sorted successfully.
        //!                 SPL_RESULT_INVALID_ARGUMENT - if the arguments passed 
        //!                 are invalid. 
        //!                 SPL_RESULT_BUFFER_ERROR - if there is an error happens
        //!                 during memory allocation or data transfer.
        //!                 SPL_RESULT_PROGRAM_ERROR - if there is an error in 
        //!                 program loading or execution.
        //!
        //! \brief The implementation of the Bitonic sort.
        //!
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        SPL_RESULT bionicSortImpl(T *ptr, unsigned int size, bool asc)
        {
            if(!ptr || size == 0)
                return SPL_RESULT_INVALID_ARGUMENT;

            Device *device = Runtime::getInstance()->getDeviceManager()->getDefaultDevice();
            if (!device)
                return SPL_RESULT_NOT_INITIALIZED;
            
            CALdeviceinfo info = device->getInfo();
            if (size <= info.maxResource1DWidth)
            {
                // the array is too small, use the stl::sort is sufficient
                if (asc)
                {
                    std::sort(ptr, ptr + size, less<T>());
                }
                else
                    std::sort(ptr, ptr + size, greater<T>());
                return SPL_RESULT_OK;
            }
            else
            {
                CALresult result = CAL_RESULT_OK;

                Runtime* runtime = Runtime::getInstance();
                BufferManager *bufMgr = runtime->getBufferManager();
                ProgramManager *progMgr = runtime->getProgramManager();

                uint bufferSize = utils::ceilPow(size);
                unsigned int _lgArraySize;
                for (_lgArraySize = 0; bufferSize >> _lgArraySize; _lgArraySize++){;}
                _lgArraySize--;

                unsigned int width = info.maxResource1DWidth;
                unsigned int height = 
                    static_cast<unsigned int>(ceil(((double)bufferSize) / width));

                Buffer* buffer1 = bufMgr->createLocalBuffer(device, utils::getElementFormat<T>(),
                    width, height);
                if (!buffer1)
                    return SPL_RESULT_BUFFER_ERROR;
                Buffer* buffer2 = bufMgr->createLocalBuffer(device, utils::getElementFormat<T>(),
                    width, height);
                if (!buffer2)
                    return SPL_RESULT_BUFFER_ERROR;

                ConstBuffer* constBuffer = bufMgr->getConstBuffer(4);
                if (!constBuffer)
                    return SPL_RESULT_BUFFER_ERROR;

                T extremeValue = asc ? extreme_value<T>::MaxValue : extreme_value<T>::MinValue;
                if(!buffer1->readData(ptr, size))
                    return SPL_RESULT_BUFFER_ERROR;

                Program *prog = progMgr->loadProgram(asc ? bitonicSortILGroup<T>::asc : bitonicSortILGroup<T>::des, device);
                if (!prog)
                {
                    return SPL_RESULT_PROGRAM_ERROR;
                }

                constBuffer->setConstant<3>(&width);
                prog->bindConstant(constBuffer, 0);

                prog->setExeInfo(
                    ProgExeInfo(uint4(0, 0, width, height))
                    );
                for(unsigned int _stage = 1; _stage <= _lgArraySize; _stage++)
                {
                    unsigned int step = 0;
                    // Width of each sorted segment to be sorted in parallel (2, 4, 8, ...)

                    for (step = 1; step <= _stage; ++step)
                    {
                        // offset = (stageWidth/2, stageWidth/4, ... , 2, 1)
                        unsigned int offset = 1 << (_stage - step);
                        unsigned int offset_2 = offset << 1;

                        if(!prog->bindInput(buffer1, 0))
                        {
                            //TODO cleanup;
                        }
                        if(!prog->bindOutput(buffer2, 0))
                        {
                            //TODO cleanup;
                        }

                        constBuffer->setConstant<0>(&_stage);
                        constBuffer->setConstant<1>(&offset);
                        constBuffer->setConstant<2>(&offset_2);

                        // Run the kernel on GPU
                        Event *e = prog->run();
                        if (!e)
                        {
                            return SPL_RESULT_PROGRAM_ERROR;
                        }

                        Buffer* tmp = buffer1;
                        buffer1 = buffer2;
                        buffer2 = tmp;
                    }
                }
                if(!buffer1->writeData(ptr, size))
                    return SPL_RESULT_BUFFER_ERROR;

                progMgr->unloadProgram(prog);
                bufMgr->releaseConstBuffer(constBuffer);
                bufMgr->destroyBuffer(buffer1);
                bufMgr->destroyBuffer(buffer2);

                return SPL_RESULT_OK;
            }
            
        }
    }
};
#endif

