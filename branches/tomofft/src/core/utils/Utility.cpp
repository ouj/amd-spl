//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		Utility.cpp
//!	\date 		1:3:2009   15:32
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of utility functions and classes.
//!
//////////////////////////////////////////////////////////////////////////
#include "Utility.h"
#include <cmath>

namespace amdspl
{
    namespace utils
    {
        ////////////////////////////////////////////////////////////////////////////////
        //!
        //! \brief Method to find the next-higher power of two
        //!
        ////////////////////////////////////////////////////////////////////////////////

        unsigned int
            ceilPow(unsigned int num)
        {
            --num;
            for(unsigned int i = 1; i < sizeof(unsigned int) * 8; i *= 2)
            {
                num |= num >> i;
            }

            return num + 1;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //!
        //! \brief Method to find the next-lower power of two
        //!
        ////////////////////////////////////////////////////////////////////////////////

        unsigned int
            floorPow(unsigned int num)
        {
            for(unsigned int i = 1; i < sizeof(unsigned int) * 8; i *= 2)
            {
                num |= num >> i;
            }

            return num - (num >> 1);
        }


        ////////////////////////////////////////////////////////////////////////////////
        //!
        //! \brief Method to find the lowest prime divisor of a number
        //!
        ////////////////////////////////////////////////////////////////////////////////

        unsigned int
            lowestPrimeDivisor(unsigned int num)
        {
            unsigned int sqrtNum = (unsigned int)(sqrt(double(num)));
            for(unsigned int i = 2; i <= sqrtNum; ++i)
            {
                if((num % i) == 0)
                {
                    return i;
                }
            }

            return num;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //!
        //! \brief Returns bytes in one element
        //!
        ////////////////////////////////////////////////////////////////////////////////

        unsigned short 
            getElementBytes(CALformat dataFormat)
        {
            switch(dataFormat)
            {
            case CAL_FORMAT_UNORM_INT8_1:
            case CAL_FORMAT_SNORM_INT8_1:
            case CAL_FORMAT_UNSIGNED_INT8_1:
            case CAL_FORMAT_SIGNED_INT8_1:
                return sizeof(char);
            case CAL_FORMAT_UNORM_INT8_2:
            case CAL_FORMAT_SNORM_INT8_2:
            case CAL_FORMAT_UNSIGNED_INT8_2:
            case CAL_FORMAT_SIGNED_INT8_2:
                return sizeof(char) * 2;
            case CAL_FORMAT_UNORM_INT8_4:
            case CAL_FORMAT_SNORM_INT8_4:
            case CAL_FORMAT_UNSIGNED_INT8_4:
            case CAL_FORMAT_SIGNED_INT8_4:
                return sizeof(char) * 4;
            case CAL_FORMAT_UNORM_INT16_1:
            case CAL_FORMAT_SNORM_INT16_1:
            case CAL_FORMAT_UNSIGNED_INT16_1:
            case CAL_FORMAT_SIGNED_INT16_1:
                return sizeof(short);
            case CAL_FORMAT_UNORM_INT16_2:
            case CAL_FORMAT_SNORM_INT16_2:
            case CAL_FORMAT_UNSIGNED_INT16_2:
            case CAL_FORMAT_SIGNED_INT16_2:
                return sizeof(short) * 2;
            case CAL_FORMAT_UNORM_INT16_4:
            case CAL_FORMAT_SNORM_INT16_4:
            case CAL_FORMAT_UNSIGNED_INT16_4:
            case CAL_FORMAT_SIGNED_INT16_4:
                return sizeof(short) * 4;
            case CAL_FORMAT_UNORM_INT32_1:
            case CAL_FORMAT_SNORM_INT32_1:
            case CAL_FORMAT_UNSIGNED_INT32_1:
            case CAL_FORMAT_SIGNED_INT32_1:
                return sizeof(int);
            case CAL_FORMAT_UNORM_INT32_2:
            case CAL_FORMAT_SNORM_INT32_2:
            case CAL_FORMAT_UNSIGNED_INT32_2:
            case CAL_FORMAT_SIGNED_INT32_2:
                return sizeof(int) * 2;
            case CAL_FORMAT_UNORM_INT32_4:
            case CAL_FORMAT_SNORM_INT32_4:
            case CAL_FORMAT_UNSIGNED_INT32_4:
            case CAL_FORMAT_SIGNED_INT32_4:
                return sizeof(int) * 4;
            case CAL_FORMAT_FLOAT32_1:
                return sizeof(float);
            case CAL_FORMAT_FLOAT32_2:
                return sizeof(float2);
            case CAL_FORMAT_FLOAT32_4:
                return sizeof(float4);
            case CAL_FORMAT_FLOAT64_1:
                return sizeof(double);
            case CAL_FORMAT_FLOAT64_2:
                return sizeof(double2);
            default:
                return 0;
            }
            return 0;
        }
    }
}

