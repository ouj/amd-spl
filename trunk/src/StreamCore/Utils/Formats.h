#ifndef _FORMATS_H_
#define _FORMATS_H_

#include "VectorDataType.h"

namespace amdspl
{

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \enum BRformat
    //!
    //! \brief Different Brook data types supported
    //!
    ////////////////////////////////////////////////////////////////////////////////

    enum BRformat
    {
        BR_FORMAT_FLOAT_1,
        BR_FORMAT_FLOAT_2,
        BR_FORMAT_FLOAT_3,
        BR_FORMAT_FLOAT_4,
        BR_FORMAT_UINT_1,
        BR_FORMAT_UINT_2,
        BR_FORMAT_UINT_3,
        BR_FORMAT_UINT_4,
        BR_FORMAT_INT_1,
        BR_FORMAT_INT_2,
        BR_FORMAT_INT_3,
        BR_FORMAT_INT_4,
        BR_FORMAT_DOUBLE_1,
        BR_FORMAT_DOUBLE_2,
        BR_FORMAT_FORCE_DWORD    = 0x7fffffff, /* force 32-bit size enum */
    };

    template<class T>
    inline BRformat* getStreamType(T*, unsigned int& count);

    template<>
    inline BRformat* getStreamType(float*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_FLOAT_1;

        return formats;
    }

    template<>
    inline BRformat* getStreamType(float2*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_FLOAT_2;

        return formats;
    }

    template<>
    inline BRformat* getStreamType(float3*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_FLOAT_3;

        return formats;
    }

    template<>
    inline BRformat* getStreamType(float4*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_FLOAT_4;

        return formats;
    }

    template<>
    inline BRformat* getStreamType(unsigned int*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_UINT_1;

        return formats;
    }

    template<>
    inline BRformat* getStreamType(uint2*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_UINT_2;

        return formats;
    }

    template<>
    inline BRformat* getStreamType(uint3*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_UINT_3;

        return formats;
    }

    template<>
    inline BRformat* getStreamType(uint4*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_UINT_4;

        return formats;
    }

    template<>
    inline BRformat* getStreamType(int*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_INT_1;

        return formats;
    }

    template<>
    inline BRformat* getStreamType(int2*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_INT_2;

        return formats;
    }

    template<>
    inline BRformat* getStreamType(int3*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_INT_3;

        return formats;
    }

    template<>
    inline BRformat* getStreamType(int4*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_INT_4;

        return formats;
    }

    template<>
    inline BRformat* getStreamType(double*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_DOUBLE_1;

        return formats;
    }

    template<>
    inline BRformat* getStreamType(double2*, unsigned int& count)
    {
        count = 1;
        BRformat* formats = new BRformat[count];
        formats[0] = BR_FORMAT_DOUBLE_2;

        return formats;
    }
}
#endif //_FORMATS_H_
