#ifndef _AMDSPL_BITONICSORT_CALCODE_H
#define _AMDSPL_BITONICSORT_CALCODE_H

#include "ILPrograms.h"

const char f_szBitonicSort[] = 
"il_ps_2_0\n"
"dcl_output_generic o0\n"
"dcl_resource_id(0)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
"dcl_input_position_interp(linear_noperspective) v0.xy__\n"
"; l0 = (0.500000f 0.500000f 0.500000f 0.500000f)\n"
"dcl_literal l0, 0x3F000000, 0x3F000000, 0x3F000000, 0x3F000000\n"
"; l1 = (0.000000f 0.000000f 0.000000f 0.000000f)\n"
"dcl_literal l1, 0x00000001, 0x00000001, 0x00000001, 0x00000001\n"
"; l2 = (-1.#QNAN0f -1.#QNAN0f -1.#QNAN0f -1.#QNAN0f)\n"
"dcl_literal l2, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF\n"
"; l3 = (2.000000f 2.000000f 2.000000f 2.000000f)\n"
"dcl_literal l3, 0x40000000, 0x40000000, 0x40000000, 0x40000000\n"
"; l4 = (0.000000f 0.000000f 0.000000f 0.000000f)\n"
"dcl_literal l4, 0x00000000, 0x00000000, 0x00000000, 0x00000000\n"
"dcl_cb cb0[1]\n"
"mov r1.xy__, v0\n"
"sub r11.x___, r1.x000, l0.x000\n"
"ftoi r11, r11\n"
"itof r11.x___, r11.x000\n"
"mod r3.x___, r11.x000, cb0[0].z000\n"
"lt r4.x___, r3.x000, cb0[0].y000\n"
"div_zeroop(infinity) r5.x___, r11.x000, cb0[0].x000\n"
"round_neginf r5.x___, r5.x000\n"
"mod r3.x___, r5.x000, l3.x000\n"
"eq r6.x___, r3.x000, l4.x000\n"
"mov o0.x___, r6.x000\n"
"endmain\n"
"end\n";

amdspl::ILProgInfo BitonicSortILInfo(void)
{
    return amdspl::ILProgInfo( "f_szBitonicSort " )
        .image(f_szBitonicSort)
        .input(1).constant(1).output(1);
}

#endif // _AMDSPL_SORT_CALCODE_H
