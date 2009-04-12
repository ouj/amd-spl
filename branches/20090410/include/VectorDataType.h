#ifndef _AMDSPL_VECTORDATATYPE_
#define _AMDSPL_VECTORDATATYPE_
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		VectorDataType.h
//!	\date 		1:3:2009   15:26
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains vector data type constructors
//!
//////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <string.h>

namespace amdspl
{
    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief float2 type.
    //!
    ////////////////////////////////////////////////////////////////////////////////
    typedef struct float2
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \param	_x  X component.
        //! \param	_y  Y component.
        //! \return	Constructor
        //!
        //! \brief	Construct the float2 type.
        //!
        //////////////////////////////////////////////////////////////////////////
        float2(float _x = 0, float _y = 0)
            :x(_x), y(_y)
        {

        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from float2 pointer to a pointer to float.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator float*()
        {
            return (float*)this;
        }

        //! \brief	X component.
        float x;
        //! \brief	Y component.
        float y;

    } float2;

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief double2 type.
    //!
    ////////////////////////////////////////////////////////////////////////////////
    typedef struct double2
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \param	_x  X component.
        //! \param	_y  Y component.
        //! \return	Constructor
        //!
        //! \brief	Construct a double2 type.
        //!
        //////////////////////////////////////////////////////////////////////////
        double2(double _x = 0, double _y = 0)
            :x(_x), y(_y)
        {

        }

        //! \brief	X component.
        double x;
        //! \brief	Y component.
        double y;

    } double2;


    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief float3 type.
    //!
    ////////////////////////////////////////////////////////////////////////////////
    typedef struct float3
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \param	_x  X component.
        //! \param	_y  Y component.
        //! \param	_z  Z component.
        //! \return	Constructor
        //!
        //! \brief	Construct a float3 type.
        //!
        //////////////////////////////////////////////////////////////////////////
        float3(float _x = 0, float _y = 0, float _z = 0)
            :x(_x), y(_y), z(_z)
        {

        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from float3 pointer to a pointer to float.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator float*()
        {
            return (float*)this;
        }

        //! \brief	X component.
        float x;
        //! \brief	Y component.
        float y;
        //! \brief	Z component.
        float z;

    } float3;

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief float4 type.
    //!
    ////////////////////////////////////////////////////////////////////////////////

    typedef struct float4
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \param	_x  X component.
        //! \param	_y  Y component.
        //! \param	_z  Z component.
        //! \param	_w  W component.
        //! \return	Constructor
        //!
        //! \brief	Construct a float4 type.
        //!
        //////////////////////////////////////////////////////////////////////////
        float4(float _x = 0, float _y = 0, float _z = 0, float _w = 0)
            :x(_x), y(_y), z(_z), w(_w)
        {

        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from float4 pointer to a pointer to float.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator float*()
        {
            return (float*)this;
        }

        //! \brief	X component.
        float x;
        //! \brief	Y component.
        float y;
        //! \brief	Z component.
        float z;
        //! \brief	W component.
        float w;

    } float4;

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief int2 type.
    //!
    ////////////////////////////////////////////////////////////////////////////////
    typedef struct int2
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \param	_x  X component.
        //! \param	_y  Y component.
        //! \return	    Constructor.
        //!
        //! \brief	Construct a int2 type.
        //!
        //////////////////////////////////////////////////////////////////////////
        int2( int _x = 0, int _y = 0 )
            : x(_x), y(_y)
        {

        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from int2 pointer to a pointer to int.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator int*()
        {
            return (int*)this;
        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from int2 pointer to a pointer to const int.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator const int*() const
        {
            return (const int*)this;
        }

        //! \brief	X component.    
        int x;
        //! \brief	Y component.
        int y;

    } int2;

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief int3 type.
    //!
    ////////////////////////////////////////////////////////////////////////////////
    typedef struct int3
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \param	_x  X component.
        //! \param	_y  Y component.
        //! \param	_z  Z component.
        //! \return	    Constructor
        //!
        //! \brief	Construct a int3 type.
        //!
        //////////////////////////////////////////////////////////////////////////
        int3( int _x = 0, int _y = 0, int _z = 0 )
            : x(_x), y(_y), z(_z)
        {

        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from int3 pointer to a pointer to const int.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator int*()
        {
            return (int*)this;
        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from int3 pointer to a pointer to const int.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator const int*() const
        {
            return (const int*)this;
        }

        //! \brief	X component.  
        int x;
        //! \brief	Y component.
        int y;
        //! \brief	Z component.
        int z;

    } int3;

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief int4 type.
    //!
    ////////////////////////////////////////////////////////////////////////////////
    typedef struct int4
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \param	_x  X component.
        //! \param	_y  Y component.
        //! \param	_z  Z component.
        //! \param	_w  W component.
        //! \return	    Constructor
        //!
        //! \brief	Construct a int4 type.
        //!
        //////////////////////////////////////////////////////////////////////////
        int4( int _x = 0, int _y = 0, int _z = 0, int _w = 0 )
            : x(_x), y(_y), z(_z), w(_w)
        {

        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from int4 pointer to a pointer to int.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator int*()
        {
            return (int*)this;
        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from int4 pointer to a pointer to const int.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator const int*() const
        {
            return (const int*)this;
        }

        //! \brief	X component.  
        int x;
        //! \brief	Y component.
        int y;
        //! \brief	Z component.
        int z;
        //! \brief	W component.
        int w;

    } int4;

    //////////////////////////////////////////////////////////////////////////
    //!
    //! \brief uint type.
    //!
    //////////////////////////////////////////////////////////////////////////
    typedef unsigned int uint;

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief uint2 type.
    //!
    ////////////////////////////////////////////////////////////////////////////////
    typedef struct uint2
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \param	_x  X component.
        //! \param	_y  Y component.
        //! \return	    Constructor
        //!
        //! \brief	Construct a uint2 type.
        //!
        //////////////////////////////////////////////////////////////////////////
        uint2( unsigned int _x = 0, unsigned int _y = 0 )
            : x(_x), y(_y)
        {

        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from uint2 pointer to a pointer to int.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator unsigned int*() 
        {
            return (unsigned int*)this;
        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from uint2 pointer to a pointer to const int.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator const unsigned int*() const
        {
            return (const unsigned int*)this; 
        }

        //! \brief	X component.  
        unsigned int x;
        //! \brief	Y component.
        unsigned int y;

    } uint2;

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief uint3 type.
    //!
    ////////////////////////////////////////////////////////////////////////////////
    typedef struct uint3
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \param	_x  X component.
        //! \param	_y  Y component.
        //! \param	_z  Z component.
        //! \return	    Constructor
        //!
        //! \brief	Construct a uint3 type.
        //!
        //////////////////////////////////////////////////////////////////////////
        uint3( unsigned int _x = 0, unsigned int _y = 0, unsigned int _z = 0 )
            : x(_x), y(_y), z(_z)
        {

        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from uint3 pointer to a pointer to int.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator unsigned int*()
        {
            return (unsigned int*)this;
        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from uint3 pointer to a pointer to const int.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator const unsigned int*() const
        {
            return (const unsigned int*)this;
        }

        //! \brief	X component.  
        unsigned int x;
        //! \brief	Y component.
        unsigned int y;
        //! \brief	Z component.
        unsigned int z;

    } uint3;

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief uint4 type.
    //!
    ////////////////////////////////////////////////////////////////////////////////
    typedef struct uint4
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \param	_x  X component.
        //! \param	_y  Y component.
        //! \param	_z  Z component.
        //! \param	_w  W component.
        //! \return	    Constructor
        //!
        //! \brief	Construct a uint4 type.
        //!
        //////////////////////////////////////////////////////////////////////////
        uint4( unsigned int _x = 0, unsigned int _y = 0, unsigned int _z = 0, unsigned int _w = 0 )
            : x(_x), y(_y), z(_z), w(_w)
        {

        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from uint4 pointer to a pointer to int.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator unsigned int*()
        {
            return (unsigned int*)this;
        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief conversion from uint4 pointer to a pointer to const int.
        //!
        //////////////////////////////////////////////////////////////////////////
        operator const unsigned int*() const
        {
            return (const unsigned int*)this;
        }

        //! \brief	X component.  
        unsigned int x;
        //! \brief	Y component.
        unsigned int y;
        //! \brief	Z component.
        unsigned int z;
        //! \brief	X component.
        unsigned int w;

    } uint4;
}

#endif //VECTORDATATYPE_HPP_
