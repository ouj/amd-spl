
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
            case CAL_FORMAT_FLOAT_1:
                return sizeof(float);
            case CAL_FORMAT_UINT_1:
                return sizeof(unsigned int);
            case CAL_FORMAT_INT_1:
                return sizeof(int);
            case CAL_FORMAT_DOUBLE_1:
                return sizeof(double);
            case CAL_FORMAT_FLOAT_2:
                return sizeof(float2);
            case CAL_FORMAT_UINT_2:
                return sizeof(uint2);
            case CAL_FORMAT_INT_2:
                return sizeof(int2);
            case CAL_FORMAT_DOUBLE_2:
                return sizeof(double2);
            case CAL_FORMAT_FLOAT_4:
                return sizeof(float4);
            case CAL_FORMAT_UINT_4:
                return sizeof(uint4);
            case CAL_FORMAT_INT_4:
                return sizeof(int4);
            default:
                return 0;
            }
            return 0;
        }
    }
}