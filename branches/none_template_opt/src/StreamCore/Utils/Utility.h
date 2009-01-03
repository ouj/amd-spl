#ifndef _AMDSPL_UTILITY_H_
#define _AMDSPL_UTILITY_H_

////////////////////////////////////////////////////////////////////////////////
//!
//! \file Utility.h
//!
//! \brief Declaration of utility class
//!
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>

#include "cal.h"

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
    }
}


#endif //_UTILITY_H_
