#ifndef _AMDSPL_UTILITY_H_
#define _AMDSPL_UTILITY_H_

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

////////////////////////////////////////////////////////////////////////////////
//!
//! \class Utility
//!
//! \brief Class containing helper methods
//!
////////////////////////////////////////////////////////////////////////////////

namespace amdspl
{
    namespace utils
    {
        unsigned int ceilPow (unsigned int num);
        unsigned int floorPow (unsigned int num);
        unsigned int lowestPrimeDivisor(unsigned int num);
        unsigned short getElementBytes(CALformat dataFormat);

        template<typename T>
        struct type_descriptor
        {
            static const char* Name;
            static const CALformat Format;
            enum
            {
                Bytes = sizeof(T)
            };
        };

        template<>
        const char* type_descriptor<int>::Name = "int";
        const CALformat type_descriptor<int>::Format = CAL_FORMAT_INT_1;

        template<>
        const char* type_descriptor<int2>::Name = "int2";
        const CALformat type_descriptor<int2>::Format = CAL_FORMAT_INT_2;

        template<>
        const char* type_descriptor<int4>::Name = "int4";
        const CALformat type_descriptor<int4>::Format = CAL_FORMAT_INT_4;

        template<>
        const char* type_descriptor<uint>::Name = "uint";
        const CALformat type_descriptor<uint>::Format = CAL_FORMAT_UINT_1;

        template<>
        const char* type_descriptor<uint2>::Name = "uint2";
        const CALformat type_descriptor<uint2>::Format = CAL_FORMAT_UINT_2;

        template<>
        const char* type_descriptor<uint4>::Name = "uint4";
        const CALformat type_descriptor<uint4>::Format = CAL_FORMAT_UINT_4;


        const char* type_descriptor<float>::Name = "float";
        const CALformat type_descriptor<float>::Format = CAL_FORMAT_FLOAT_1;

        template<>
        const char* type_descriptor<float2>::Name = "float2";
        const CALformat type_descriptor<float2>::Format = CAL_FORMAT_FLOAT_2;

        template<>
        const char* type_descriptor<float4>::Name = "float4";
        const CALformat type_descriptor<float4>::Format = CAL_FORMAT_FLOAT_4;

        template<>
        const char* type_descriptor<double>::Name = "double";
        const CALformat type_descriptor<double>::Format = CAL_FORMAT_DOUBLE_1;

        template<>
        const char* type_descriptor<double2>::Name = "double2";
        const CALformat type_descriptor<double2>::Format = CAL_FORMAT_DOUBLE_2;
    }
}


#endif //_UTILITY_H_
