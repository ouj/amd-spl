#include "util.h"
#include "stdio.h"

namespace util
{
    void printDeviceStatus(Device* device)
    {
        CALdevicestatus status = device->getStatus();
        printf("\tLocalRam: %d, UncachedRemoteRam: %d, CachedRemoteRam: %d\n", 
            status.availLocalRAM, status.availUncachedRemoteRAM, status.availCachedRemoteRAM);
    }

    // Value functions
    template<>
    void 
        value(float2& var,
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type)
    {
        value(var.x, x, y, width, height, bound, type);
        value(var.y, x, y, width, height, bound, type);
    }

    template<>
    void 
        value(float3& var,
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type)
    {
        value(var.x, x, y, width, height, bound, type);
        value(var.y, x, y, width, height, bound, type);
        value(var.z, x, y, width, height, bound, type);
    }

    template<>
    void 
        value(float4& var, 
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type)
    {
        value(var.x, x, y, width, height, bound, type);
        value(var.y, x, y, width, height, bound, type);
        value(var.z, x, y, width, height, bound, type);
        value(var.w, x, y, width, height, bound, type);
    }

    template<>
    void 
        value(int2& var, 
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type)
    {
        value(var.x, x, y, width, height, bound, type);
        value(var.y, x, y, width, height, bound, type);
    }

    template<>
    void 
        value(int3& var, 
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type)
    {
        value(var.x, x, y, width, height, bound, type);
        value(var.y, x, y, width, height, bound, type);
        value(var.z, x, y, width, height, bound, type);
    }

    template<>
    void 
        value(int4& var, 
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type)
    {
        value(var.x, x, y, width, height, bound, type);
        value(var.y, x, y, width, height, bound, type);
        value(var.z, x, y, width, height, bound, type);
        value(var.w, x, y, width, height, bound, type);
    }

    template<>
    void 
        value(uint2& var, 
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type)
    {
        value(var.x, x, y, width, height, bound, type);
        value(var.y, x, y, width, height, bound, type);
    }

    template<>
    void 
        value(uint3& var, 
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type)
    {
        value(var.x, x, y, width, height, bound, type);
        value(var.y, x, y, width, height, bound, type);
        value(var.z, x, y, width, height, bound, type);
    }

    template<>
    void 
        value(uint4& var, 
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type)
    {
        value(var.x, x, y, width, height, bound, type);
        value(var.y, x, y, width, height, bound, type);
        value(var.z, x, y, width, height, bound, type);
        value(var.w, x, y, width, height, bound, type);
    }

    template<>
    void 
        value(double2& var, 
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type)
    {
        value(var.x, x, y, width, height, bound, type);
        value(var.y, x, y, width, height, bound, type);
    }

    template <>
    bool
        compare(const int2 val0, const int2 val1)
    {
        return (compare(val0.x, val1.x) && compare(val0.y,val1.y));
    }

    template <>
    bool
        compare(const int3 val0, const int3 val1)
    {
        return (compare(val0.x, val1.x) && 
            compare(val0.y,val1.y) &&
            compare(val0.z, val1.z));
    }

    template <>
    bool
        compare(const int4 val0, const int4 val1)
    {
        return (compare(val0.x, val1.x) && 
            compare(val0.y,val1.y) &&
            compare(val0.z, val1.z) &&
            compare(val0.w, val1.w));
    }

    // Compare functions
    template <>
    bool
        compare(const float val0, const float val1)
    {
        const float epsilon = (float)1e-2;
        float diff = (val1 - val0);
        if (fabs(val1) > epsilon)
        {
            diff /= val0;
        }

        return (fabs(diff) < epsilon);
    }

    template <>
    bool
        compare(const float2 val0, const float2 val1)
    {
        return (compare(val0.x, val1.x) && compare(val0.y,val1.y));
    }

    template <>
    bool
        compare(const float3 val0, const float3 val1)
    {
        return (compare(val0.x, val1.x) && 
            compare(val0.y,val1.y) &&
            compare(val0.z, val1.z));
    }

    template <>
    bool
        compare(const float4 val0, const float4 val1)
    {
        return (compare(val0.x, val1.x) && 
            compare(val0.y,val1.y) &&
            compare(val0.z, val1.z) &&
            compare(val0.w, val1.w));
    }

    template <>
    bool
        compare(const double val0, const double val1)
    {
        const double epsilon = (double)1e-2;
        double diff = (val1 - val0);
        if (fabs(val1) > epsilon)
        {
            diff /= val0;            
        }

        return (fabs(diff) < epsilon);
    }

    template <>
    bool
        compare(const double2 val0, const double2 val1)
    {
        return (compare(val0.x, val1.x) && compare(val0.y,val1.y));
    }

}