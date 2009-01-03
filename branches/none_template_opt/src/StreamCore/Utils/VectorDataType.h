#ifndef _AMDSPL_VECTORDATATYPE_
#define _AMDSPL_VECTORDATATYPE_

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
