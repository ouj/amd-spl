#ifndef AMDSPL_UTILITY_H
#define AMDSPL_UTILITY_H

////////////////////////////////////////////////////////////////////////////////
//!
//! \file Utility.h
//!
//! \brief Contains declaration of utility functions and classes.
//!
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>
#include <float.h>

#include "cal.h"
#include "VectorDataType.h"

namespace amdspl
{
    namespace utils
    {
        unsigned int ceilPow (unsigned int num);
        unsigned int floorPow (unsigned int num);
        unsigned int lowestPrimeDivisor(unsigned int num);
        unsigned short getElementBytes(CALformat dataFormat);

        template<typename T>
        inline CALformat getElementFormat();
        
        template<>
        inline CALformat getElementFormat<int>(){ return CAL_FORMAT_INT_1; };

        template<>
        inline CALformat getElementFormat<int2>(){ return CAL_FORMAT_INT_2; };

        template<>
        inline CALformat getElementFormat<int4>(){ return CAL_FORMAT_INT_4; };

        template<>
        inline CALformat getElementFormat<uint>(){ return CAL_FORMAT_UINT_1; };

        template<>
        inline CALformat getElementFormat<uint2>(){ return CAL_FORMAT_UINT_2; };

        template<>
        inline CALformat getElementFormat<uint4>(){ return CAL_FORMAT_UINT_4; };

        template<>
        inline CALformat getElementFormat<float>(){ return CAL_FORMAT_FLOAT_1; };

        template<>
        inline CALformat getElementFormat<float2>(){ return CAL_FORMAT_FLOAT_2; };

        template<>
        inline CALformat getElementFormat<float4>(){ return CAL_FORMAT_FLOAT_4; };

        template<>
        inline CALformat getElementFormat<double>(){ return CAL_FORMAT_DOUBLE_1; };

        template<>
        inline CALformat getElementFormat<double2>(){ return CAL_FORMAT_DOUBLE_2; };

        template<>
        inline CALformat getElementFormat<char>(){ return CAL_FORMAT_BYTE_1; };

        template<>
        inline CALformat getElementFormat<short>(){ return CAL_FORMAT_SHORT_1; };
    }
}


#endif //AMDSPL_UTILITY_H
