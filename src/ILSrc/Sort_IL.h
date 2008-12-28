#ifndef _AMDSPL_BITONICSORT_CALCODE_H
#define _AMDSPL_BITONICSORT_CALCODE_H

#include "ILPrograms.h"

const char f_szBitonicSort[] = 
"il_ps_2_0\n"
"dcl_output_generic o0\n"
"dcl_resource_id(0)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
"dcl_input_position_interp(linear_noperspective) v0.xy__\n"
"; l0 = (0.500000f 2.000000f 0.000000f 1.000000f)\n"
"dcl_literal l0, 0x3F000000, 0x40000000, 0x00000000, 0x3F800000\n"
"dcl_cb cb0[1]\n"
"mov r1.xy__, v0\n"
"sub r1.x___, r1.x000, l0.x000\n"
"ftoi r1, r1\n"
"itof r1.x___, r1.x000\n"
"mod r3.x___, r1.x000, cb0[0].z000\n"
"sub r3.x___, r3.x000, cb0[0].y000\n"
"sub r3.x___, r3.x000, l0.x000\n"
"sgn r3.x___, r3.x000\n"
"div_zeroop(infinity) r4.x___, r1.x000, cb0[0].x000\n"
"round_neginf r4.x___, r4.x000\n"
"mod r4.x___, r4.x000, l0.y000\n"
"eq r4.x___, r4.x000, l0.z000\n"
"cmov_logical r4.x___, r4.x000, l0.w000, l0.w000_neg(xyzw)\n"
"mov o0.x___, r4.x000\n"
"endmain\n"
"end\n";


amdspl::ILProgInfo BitonicSortILInfo(void)
{
    return amdspl::ILProgInfo( "f_szBitonicSort " )
        .image(f_szBitonicSort)
        .input(1).constant(3).output(1);
}

#endif // _AMDSPL_SORT_CALCODE_H
