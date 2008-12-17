#ifndef VECTORDATATYPE_HPP_
#define VECTORDATATYPE_HPP_

/****************************************************************************

Copyright (c) 2003, Stanford University
All rights reserved.

Copyright (c) 2008, Advanced Micro Devices, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

  * Neither the name of Stanford University nor the names of any contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

****************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//!
//! \file VectorDataType.h
//!
//! \brief Contains vector data type constructors
//!
////////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <string.h>


////////////////////////////////////////////////////////////////////////////////
//!
//! \struct float2
//!
//! \brief contains float2 constructors.
//!
////////////////////////////////////////////////////////////////////////////////

typedef struct float2
{
    float2(float _x = 0, float _y = 0)
        :x(_x), y(_y)
    {
        
    }

    operator float*()
    {
        return (float*)this;
    }

    float x,y;

} float2;

////////////////////////////////////////////////////////////////////////////////
//!
//! \struct double2
//!
//! \brief contains double2 constructors.
//!
////////////////////////////////////////////////////////////////////////////////

typedef struct double2
{
    double2(double _x = 0, double _y = 0)
        :x(_x), y(_y)
    {
        
    }

    double x,y;

} double2;

////////////////////////////////////////////////////////////////////////////////
//!
//! \struct float3
//!
//! \brief contains float3 constructors.
//!
////////////////////////////////////////////////////////////////////////////////

typedef struct float3
{
    float3(float _x = 0, float _y = 0, float _z = 0)
        :x(_x), y(_y), z(_z)
    {

    }

    operator float*()
    {
        return (float*)this;
    }

    float x,y,z;

} float3;

////////////////////////////////////////////////////////////////////////////////
//!
//! \struct float4
//!
//! \brief contains float4 constructors.
//!
////////////////////////////////////////////////////////////////////////////////

typedef struct float4
{
    float4(float _x = 0, float _y = 0, float _z = 0, float _w = 0)
        :x(_x), y(_y), z(_z), w(_w)
    {
     
    }

    operator float*()
    {
        return (float*)this;
    }

    float x,y,z,w;

} float4;

////////////////////////////////////////////////////////////////////////////////
//!
//! \struct int2
//!
//! \brief contains int2 constructors.
//!
////////////////////////////////////////////////////////////////////////////////

typedef struct int2
{
    int2( int _x = 0, int _y = 0 )
        : x(_x), y(_y)
    {
    
    }

    operator int*()
    {
        return (int*)this;
    }

    operator const int*() const
    {
        return (const int*)this;
    }
    
    int x, y;

} int2;

////////////////////////////////////////////////////////////////////////////////
//!
//! \struct int3
//!
//! \brief contains int3 constructors.
//!
////////////////////////////////////////////////////////////////////////////////

typedef struct int3
{
    int3( int _x = 0, int _y = 0, int _z = 0 )
        : x(_x), y(_y), z(_z)
    {
    
    }

    operator int*()
    {
        return (int*)this;
    }

    operator const int*() const
    {
        return (const int*)this;
    }
    
    int x, y, z;

} int3;

////////////////////////////////////////////////////////////////////////////////
//!
//! \struct int4
//!
//! \brief contains int4 constructors.
//!
////////////////////////////////////////////////////////////////////////////////

typedef struct int4
{
    int4( int _x = 0, int _y = 0, int _z = 0, int _w = 0 )
        : x(_x), y(_y), z(_z), w(_w)
    {
    
    }

    operator int*()
    {
        return (int*)this;
    }

    operator const int*() const
    {
        return (const int*)this;
    }

    int x, y, z, w;

} int4;

typedef unsigned int uint;

////////////////////////////////////////////////////////////////////////////////
//!
//! \struct uint2
//!
//! \brief contains uint2 constructors.
//!
////////////////////////////////////////////////////////////////////////////////

typedef struct uint2
{
    uint2( unsigned int _x = 0, unsigned int _y = 0 )
        : x(_x), y(_y)
    {
    
    }

    operator unsigned int*() 
    {
        return (unsigned int*)this;
    }

    operator const unsigned int*() const
    {
        return (const unsigned int*)this; 
    }

    unsigned int x, y;

} uint2;

////////////////////////////////////////////////////////////////////////////////
//!
//! \struct uint3
//!
//! \brief contains uint3 constructors.
//!
////////////////////////////////////////////////////////////////////////////////

typedef struct uint3
{
    uint3( unsigned int _x = 0, unsigned int _y = 0, unsigned int _z = 0 )
        : x(_x), y(_y), z(_z)
    {

    }

    operator unsigned int*()
    {
        return (unsigned int*)this;
    }

    operator const unsigned int*() const
    {
        return (const unsigned int*)this;
    }

    unsigned int x, y, z;

} uint3;

////////////////////////////////////////////////////////////////////////////////
//!
//! \struct uint4
//!
//! \brief contains uint4 constructors.
//!
////////////////////////////////////////////////////////////////////////////////

typedef struct uint4
{
    uint4( unsigned int _x = 0, unsigned int _y = 0, unsigned int _z = 0, unsigned int _w = 0 )
        : x(_x), y(_y), z(_z), w(_w)
    {
    
    }

    operator unsigned int*()
    {
        return (unsigned int*)this;
    }

    operator const unsigned int*() const
    {
        return (const unsigned int*)this;
    }

    unsigned int x, y, z, w;

} uint4;

#endif //VECTORDATATYPE_HPP_
