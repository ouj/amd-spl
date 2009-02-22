#include "math.h"
namespace util
{
    template <class T>
    void
        initializeBuffer(vector<T> &buffer,
        const unsigned int width, const unsigned int kheight, 
        const unsigned int bound, const BufferValue type)
    {
        unsigned int height = kheight == 0 ? 1 : kheight; //1D

        assert(buffer.size() >= width * height);

        for(unsigned int i = 0; i < height; ++i)
        {
            for(unsigned int j = 0; j < width; ++j)
            {
                //if (type == util::PREVRAND)
                //{
                //    int index = i * width + j;
                //    if (index)
                //    {
                //        value(buffer[index], j, i, width, height, bound, type);
                //        buffer[index] = buffer[index - 1] + buffer[index];
                //    }
                //    else
                //    {
                //        value(buffer[i * width + j], j, i, width, height , bound, type);
                //    }
                //}
                //else
                //{
                    value(buffer[i * width + j], j, i, width, height, bound, type);
                //}

            }
        }
    }

    template<class T>
    int compareBuffers(const vector<T> &buffer1, const vector<T> &buffer2, const unsigned int size)
    {
        assert(size <= buffer1.size() && size <= buffer2.size());
        int nequal = 0;
        for (unsigned int i = 0; i < buffer1.size(); ++i)
        {
            if (!(compare(buffer1[i], buffer2[i])))
            {
                nequal++;
            }
        }
        return nequal;    
    }


    template<class T>    
    bool
        compare(const T val0, const T val1)
    {
        return (val0 == val1);
    }

    template <>
    bool
        compare(const int2 val0, const int2 val1);

    template <>
    bool
        compare(const int3 val0, const int3 val1);

    template <>
    bool
        compare(const int4 val0, const int4 val1);

    template <>
    bool
        compare(const float val0, const float val1);

    template <>
    bool
        compare(const float2 val0, const float2 val1);

    template <>
    bool
        compare(const float3 val0, const float3 val1);

    template <>
    bool
        compare(const float4 val0, const float4 val1);

    template <>
    bool
        compare(const double val0, const double val1);

    template <>
    bool
        compare(const double2 val0, const double2 val1);

    template<class T>
    void 
        value(T& var,
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type)
    {
        switch(type)
        {
        case RANDOM:
            var = (T)((rand() / ((float)RAND_MAX + 1)) * bound);
            break;
        case PREVRAND:
            var = (T)((rand() / ((float)RAND_MAX + 1)) * bound);
            break;
        case LINEAR:
            var = (T)((y * width + x) % bound);
            break;
        case RLINEAR:
            var = (T)((float)(((width * height) - (y * width + x)) % bound));
            break;
        case ILINEAR:
            var = (T)((float)((x * width + y) % bound));
            break;
        case POS:
            var = (T)((float)(y * width + x));
            break;
        case LINEAR_INT:
            var = (T)(ceil((float)(y * width + x)));
            break;
        case RANDOM_INT:
            var = (T)(ceil((rand() / ((float)RAND_MAX + 1)) * bound));
            break;
        case CONSTANT:
            var = (T)((float)(bound));
            break;
        case POSX:
            var = (T)x;
            break;
        case POSY:
            var = (T)((float)(y));
            break;
        default:
            var = (T)(0.0);
        }
    }

    template<>
    void 
        value(float2& var,
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type);

    template<>
    void 
        value(float3& var,
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type);

    template<>
    void 
        value(float4& var, 
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type);

    template<>
    void 
        value(int2& var, 
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type);

    template<>
    void 
        value(int3& var,
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type);

    template<>
    void 
        value(int4& var,
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type);

    template<>
    void 
        value(uint2& var,
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type);

    template<>
    void 
        value(uint3& var,
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type);

    template<>
    void 
        value(uint4& var,
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type);

    template<>
    void 
        value(double2& var,
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height,
        const unsigned int bound, const BufferValue type);
}