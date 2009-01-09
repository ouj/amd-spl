#ifndef _AMDSPL_BITONICSORT_CALCODE_H
#define _AMDSPL_BITONICSORT_CALCODE_H

#include "ILParaInfo.h"
#include "ILParaList.h"

namespace amdspl
{
        enum SORT_ILPROGRAMS_INDEX
        {
            BITONIC_INIT_IL,
            BITONIC_SORT_IL,
            BITONIC_SORT_AT_IL
        };

        typedef AppendILPara<ILParaEnd,     ILParaInfo<BITONIC_SORT_IL, 1, 1, 3>>::Result       T1; // BITONIC_SORT_IL
        typedef AppendILPara<T1,            ILParaInfo<BITONIC_SORT_AT_IL, 1, 1, 4>>::Result    T2; // BITONIC_SORT_AT_IL
        typedef AppendILPara<T2,            ILParaInfo<BITONIC_INIT_IL, 0, 1, 1>>::Result       T3; // BITONIC_INIT_IL
        typedef T3                                                                              SORT_ILPARA_LIST;

        const char* ILParaByID<SORT_ILPARA_LIST, BITONIC_INIT_IL>::Result::Image = 
            "il_ps_2_0\n"
            "dcl_output_generic o0\n"
            "dcl_input_position_interp(linear_noperspective) v0.xy__\n"
            "dcl_cb cb0[1]\n"
            "mov o0, cb0[0]\n"
            "endmain\n"
            "end\n";

        const char* ILParaByID<SORT_ILPARA_LIST, BITONIC_SORT_IL>::Result::Image = 
            "il_ps_2_0\n"
            "dcl_output_generic o0\n"
            "dcl_resource_id(0)_type(1d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
            "dcl_input_position_interp(linear_noperspective) v0.xy__\n"
            "dcl_literal l1, 0xFFFFFFFF, 0x00000001, 0x00000000, 0xFFFFFFFF\n"
            "dcl_cb cb0[4]\n"
            "mov r1.xy__, v0\n"
            "sample_resource(0)_sampler(0) r11, r1.x000\n"
            "ftoi r1.x___, r1.x000\n"
            "iadd r10.x___, cb0[2].x000, l1.x000\n"
            "and r3.x___, r1.x000, r10.x000\n"
            "ilt r3.x___, r3.x000, cb0[1].x000\n"
            "cmov_logical r3.x___, r3.x000, l1.y000, l1.x000\n"
            "ishr r4.x___, r1.x000, cb0[0].x000\n"
            "and r4.x___, r4.x000, l1.y000\n"
            "ieq r4.x___, r4.x000, l1.z000\n"
            "cmov_logical r4.x___, r4.x000, l1.y000, l1.x000\n"
            "imul r2.x___, r3.x000, cb0[1].x000\n"
            "iadd r2.x___, r2.x000, r1.x000\n"
            "itof r2.x___, r2.x000\n"
            "sample_resource(0)_sampler(0) r22, r2.x000\n"
            "lt r100, r11, r22\n"
            "cmov_logical r5, r100, r11, r22\n"
            "cmov_logical r6, r100, r22, r11\n"
            "ieq r44, r3.x000, r4.x000\n"
            "cmov_logical o0, r44, r5, r6\n"
            "endmain\n"
            "end\n";

        const char* ILParaByID<SORT_ILPARA_LIST, BITONIC_SORT_AT_IL>::Result::Image = 
            "il_ps_2_0\n"
            "dcl_output_generic o0\n"
            "dcl_resource_id(0)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
            "dcl_input_position_interp(linear_noperspective) v0.xy__\n"
            "dcl_literal l0, 0x3F000000, 0x3F000000, 0x3F000000, 0x3F000000\n"
            "dcl_literal l1, 0xFFFFFFFF, 0x00000001, 0x00000000, 0xFFFFFFFF\n"
            "dcl_cb cb0[4]\n"
            "mov r1.xy__, v0\n"
            "sample_resource(0)_sampler(0) r11, r1.xy00\n"
            "ftoi r1.xy__, r1.xy00\n"
            "imul r1._y__, r1.0y00, cb0[3].0x00\n"
            "iadd r1.x___, r1.y000, r1.x000\n"
            "iadd r10.x___, cb0[2].x000, l1.x000\n"
            "and r3.x___, r1.x000, r10.x000\n"
            "ilt r3.x___, r3.x000, cb0[1].x000\n"
            "cmov_logical r3.x___, r3.x000, l1.y000, l1.x000\n"
            "itof r4.x___, r1.x000\n"
            "itof r5.x___, cb0[0].x000\n"
            "div_zeroop(infinity) r4.x___, r4.x000, r5.x000\n"
            "ftoi r4.x___, r4.x000\n"
            "and r4.x___, r4.x000, l1.y000\n"
            "ieq r4.x___, r4.x000, l1.z000\n"
            "cmov_logical r4.x___, r4.x000, l1.y000, l1.x000\n"
            "imul r2.x___, r3.x000, cb0[1].x000\n"
            "iadd r2.x___, r2.x000, r1.x000\n"
            "itof r2.x___, r2.x000\n"
            "itof r8.x___, cb0[3].x000\n"
            "div_zeroop(infinity) r2._y__, r2.0x00, r8.0x00\n"
            "round_neginf r2._y__, r2.0y00\n"
            "mul_ieee r7.x___, r8.x000, r2.y000\n"
            "sub r2.x___, r2.x000, r7.x000\n"
            "mul_ieee r2._y__, r2.0y00, r8.0x00\n"
            "add r2.x___, r2.y000, r2.x000\n"
            "mov o0, r2\n"
            "endmain\n"
            "end\n";
}
#endif // _AMDSPL_SORT_CALCODE_H
