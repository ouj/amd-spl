#ifndef _AMDSPL_BITONICSORT_CALCODE_H
#define _AMDSPL_BITONICSORT_CALCODE_H

#include "ILPrograms.h"

const char f_szBitonicSort[] = 
"il_ps_2_0\n"
"; l0 = (1.000000f 1.000000f 1.000000f 1.000000f)\n"
"dcl_literal l0, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000\n"
"dcl_output_generic o0\n"
"mov o0.x___, l0.x000\n"
"endmain\n"
"end\n";


amdspl::ILProgInfo BitonicSortILInfo(void)
{
    return amdspl::ILProgInfo( "f_szBitonicSort " )
        .image(f_szBitonicSort)
        .output(1, 0);
}

#endif // _AMDSPL_SORT_CALCODE_H
