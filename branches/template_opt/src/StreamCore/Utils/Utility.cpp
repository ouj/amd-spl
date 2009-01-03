
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
            unsigned short numComponents = 0;
            unsigned short bytes = 0;

            switch(dataFormat)
            {
            case CAL_FORMAT_FLOAT_1:
                numComponents = 1;
                bytes = sizeof(float);
                break;

            case CAL_FORMAT_UINT_1:
            case CAL_FORMAT_INT_1:
                numComponents = 1;
                bytes = sizeof(int);
                break;

            case CAL_FORMAT_DOUBLE_1:
                numComponents = 1;
                bytes = sizeof(double);
                break;

            case CAL_FORMAT_FLOAT_2:
                numComponents = 2;
                bytes = sizeof(float);
                break;

            case CAL_FORMAT_UINT_2:
            case CAL_FORMAT_INT_2:
                numComponents = 2;
                bytes = sizeof(int);
                break;

            case CAL_FORMAT_DOUBLE_2:
                numComponents = 2;
                bytes = sizeof(double);
                break;

            case CAL_FORMAT_FLOAT_4:
                numComponents = 4;
                bytes = sizeof(float);
                break;

            case CAL_FORMAT_UINT_4:
            case CAL_FORMAT_INT_4:
                numComponents = 4;
                bytes = sizeof(int);
                break;

            default:
                numComponents = 0;
                bytes = 0;
            }

            return numComponents * bytes;
        }
    }
}