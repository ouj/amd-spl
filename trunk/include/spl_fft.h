#ifndef __SPL_FFT_H__
#define __SPL_FFT_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef void * splfftHandle;

typedef float splfftReal;
typedef float splfftComplex[2];

typedef double splfftReal64;
typedef double splfftComplex64[2];

typedef enum splfftResult_t {
    SPLFFT_SUCCESS = 0,
    SPLFFT_INVALID_PLAN,
    SPLFFT_ALLOC_FAILED, 
    SPLFFT_INVALID_TYPE,
    SPLFFT_INVALID_VALUE, 
    SPLFFT_INTERNAL_ERROR,
    SPLFFT_EXEC_FAILED, 
    SPLFFT_SETUP_FAILED,
    SPLFFT_SHUTDOWN_FAILED, 
    SPLFFT_INVALID_SIZE,
} splfftResult;

typedef enum splMemcpyType_t {
    splMemcpyHostToHost = 0,
    splMemcpyDeviceToHost,
    splMemcpyHostToDevice,
    splMemcpyDeviceToDevice,
} splMemcpyType;

typedef enum splfftType_t {
    SPLFFT_R2C = 0x01,  // Real to complex (interleaved)
    SPLFFT_C2R = 0x02,  // Complex (interleaved) to real
    SPLFFT_C2C = 0x03,  // Complex to complex, interleaved

    SPLFFT_R2C_64 = 0x11,  // Real64 to complex64 (interleaved)
    SPLFFT_C2R_64 = 0x12,  // Complex64 (interleaved) to real64
    SPLFFT_C2C_64 = 0x13,  // Complex64 to complex64, interleaved
} splfftType;

// Functions
splfftResult splfftPlan1d(splfftHandle * plan, int nx, splfftType type, int batch);
splfftResult splfftPlan2d(splfftHandle * plan, int nx, int ny, splfftType type);
splfftResult splfftPlan3d(splfftHandle * plan, int nx, int ny, int nz, splfftType type);

splfftResult splfftDestroy(splfftHandle plan);

splfftResult splfftMalloc(void ** pptr, size_t bytes);
splfftResult splfftFree(void * ptr);

splfftResult splfftMemcpy(void * dst, void * src, size_t bytes, splMemcpyType type);

splfftResult splfftExecute(splfftHandle plan, void * idata, void * odata, int direction);

#ifdef __cplusplus
}
#endif

#endif

