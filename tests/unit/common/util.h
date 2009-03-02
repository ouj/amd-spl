#ifndef _TEST_UTIL_H_
#define _TEST_UTIL_H_

#include <vector>
#include "VectorDataType.h"
#include "Device.h"

using namespace std;
using namespace amdspl::core::cal;

namespace util
{
    enum BufferValue
    {
        ZERO,               // Flag to fill with zero's
        RANDOM,             // Fill method of using low order random bits
        LINEAR,             // Assigns the numbers linearly
        RLINEAR,            // Assigns the numbers in reverse linear
        ILINEAR,            // Assigns the numbers in inverse linear
        POS,                // Assigns the position
        LINEAR_INT,         // Assigns integers linearly
        RANDOM_INT,         // Assigns integers randomly
        CONSTANT,           // Assigns the bound as the constant value
        POSX,               // Assigns only the x location
        POSY,               // Assigns only the y location
        NONZERO_RANDOM      // Assigns a non zero random number (float/double)
    };

    void printDeviceStatus(Device* device);

    template <class T>
    void initializeBuffer(vector<T> &buffer,
        const unsigned int width, unsigned height, 
        const unsigned int bound, const BufferValue type = RANDOM);

    template<class T>
    int compareBuffers(const vector<T> &buffer1, const vector<T> &buffer2, const unsigned int size);

    template<class T>
    void 
        value(T& var,
        const unsigned int x, const unsigned int y, const unsigned int z,
        const unsigned int width, const unsigned int height, unsigned int depth,
        const unsigned int bound, const BufferValue type);

    template<class T>    
    bool
        compare(const T val0, const T val1);
};

#include "utilDefs.h"

#endif //_TEST_UTIL_H_