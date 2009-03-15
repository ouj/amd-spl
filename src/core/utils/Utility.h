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
        struct type_descriptor
        {
            static const char* Name;
            static const CALformat Format;
            enum { Bytes = sizeof(T)};
        };
    }
}


#endif //AMDSPL_UTILITY_H
