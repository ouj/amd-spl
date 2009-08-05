#include <iostream>
using namespace std;
#include <math.h>
#include <float.h>

#include "amdspl.h"
#include "RuntimeDefs.h"
#include "SplFFT.h"
#include "PerfCounter.h"

#include "../include/Timer.h"

using namespace amdspl;
using namespace amdspl::core::cal;

#define ATI_DEVICE_ID 1
#define VERBOSE 0
#define VERIFY 0

void generateTestData(float2* pData, unsigned int size, unsigned int batchSize) 
{
    for (unsigned int i = 0; i < size; i++)
    {
        pData->x = (rand()/(float)RAND_MAX)*2-1;
        pData->y = (rand()/(float)RAND_MAX)*2-1;
        //pData->x = (float)(i % batchSize);
        //pData->y = 0;
        pData++;
    }
}

inline double2 operator*( double2 a, double2 b ) { return double2( a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x ); }
inline double2 operator+( double2 a, double2 b ) { return double2( a.x + b.x, a.y + b.y ); }
inline double2 operator-( double2 a, double2 b ) { return double2( a.x - b.x, a.y - b.y ); }
#define M_PI 3.14159265358979323846

inline float2 operator*( float2 a, float2 b ) { return float2( a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x ); }


#if VERIFY=1

void computeFFTReference( float2 *dst, float2 *src, int n, int batch )
{   
    double2 *X = new double2[n];
    double2 *Y = new double2[n];
    for( int ibatch = 0; ibatch < batch; ibatch++ )
    {
        // go to double precision
        for( int i = 0; i < n; i++ )
            X[i] = double2( src[i].x, src[i].y );

        // FFT in double precision
        for( int kmax = 1, jmax = n/2; kmax < n; kmax *= 2, jmax /= 2 )
        {
            for( int k = 0; k < kmax; k++ )
            {
                double phi = -2.0 * M_PI * k /(2.0 * kmax);
                double2 w = double2( cos(phi), sin(phi) ); 
                for( int j = 0; j < jmax; j++ )
                {
                    Y[j*2*kmax + k]        = X[j*kmax + k] + w * X[j*kmax + n/2 + k];
                    Y[j*2*kmax + kmax + k] = X[j*kmax + k] - w * X[j*kmax + n/2 + k];
                }
            }
            double2 *T = X;
            X = Y;
            Y = T;
        }
        // return to single precision
        for( int i = 0; i < n; i++ )
            dst[i] = float2( (float)X[i].x, (float)X[i].y );
        src += n;
        dst += n;
    }
    delete [] X;
    delete [] Y;
}

void computeIFFTReference( float2 *dst, float2 *src, int n, int batch )
{   
    double2 *X = new double2[n];
    double2 *Y = new double2[n];
    for( int ibatch = 0; ibatch < batch; ibatch++ )
    {
        // go to double precision
        for( int i = 0; i < n; i++ )
            X[i] = double2( src[i].x, src[i].y );

        // FFT in double precision
        for( int kmax = 1, jmax = n/2; kmax < n; kmax *= 2, jmax /= 2 )
        {
            for( int k = 0; k < kmax; k++ )
            {
                double phi = 2.0 * M_PI * k /(2.0 * kmax);
                double2 w = double2( cos(phi), sin(phi) ); 
                for( int j = 0; j < jmax; j++ )
                {
                    Y[j*2*kmax + k]        = X[j*kmax + k] + w * X[j*kmax + n/2 + k];
                    Y[j*2*kmax + kmax + k] = X[j*kmax + k] - w * X[j*kmax + n/2 + k];
                }
            }
            double2 *T = X;
            X = Y;
            Y = T;
        }
        // return to single precision
        for( int i = 0; i < n; i++ )
            dst[i] = float2( (float)X[i].x / n, (float)X[i].y / n);
        src += n;
        dst += n;
    }
    delete [] X;
    delete [] Y;
}


const float ulp =  1.192092896e-07f;
inline float norm2( float2 a ) { return a.x*a.x+a.y*a.y ; }
inline float2 operator-( float2 a, float2 b ) { return float2( a.x - b.x, a.y - b.y ); }
//inline float max( float a, float b ) { return a > b ? a : b; }

//  
//	The relative forward error is bound by ~logN, see Th. 24.2 in:
//  
//  Higham, N. J. 2002. Accuracy and Stability of Numerical Algorithms, SIAM.
//    (Available online at http://books.google.com/books?id=epilvM5MMxwC)
//  
float relative_error( float2 *reference, float2 *result, int n, int batch )
{   
    float error = 0;
    for( int i = 0; i < batch; i++ )
    {
        float diff = 0, norm = 0;
        for( int j = 0; j < n; j++ )
        {
            diff += norm2( reference[j] - result[j] );
            norm += norm2( reference[j] );
        }
        if( _isnan( diff ) )
            return -1;
        
        error = max( error, diff / norm );
        
        reference += n;
        result += n;
    }
    return sqrt( error ) / ulp;
}   

void verifyData(float2 *d, float2 *r, int n, int batch)
{
	float ulps = relative_error(r,d,n/batch,batch);
	printf("error = %.1lf \n", ulps);
}

#else
void computeFFTReference( float2 *dst, float2 *src, int n, int batch ) {;}
void computeIFFTReference( float2 *dst, float2 *src, int n, int batch ) {;}
#define verifyData(d,r,n,b)

#endif


void printData(float2* pData, unsigned int size, unsigned int batchSize) 
{
#if VERBOSE=1
	for (unsigned int i = 0; i < size; i++)
    {
        printf("%.2f:%.2f  ", pData->x, pData->y);
        pData++;
        if (i % batchSize == batchSize - 1)
        {
            printf("\n");
        }
    }
#endif
}

int 
testFFT(float2 * idata, float2 * odata, int nx, int n_batch)
{
    CPerfCounter timerc;

    float2 *result = (float2 *)_aligned_malloc(sizeof(float2) * nx * n_batch, 4096);
    computeFFTReference(result, idata, nx, n_batch);
    printData(result, nx, nx);

    amdspl::fft::FFTplan fftp;

    if (fftp.init_1d(nx, n_batch))
    {
        printf("Failed to plan! \n");
        return 1;
    }
    printf("FFT%d planned! \n", nx);

    timerc.Start();
    if (fftp.execute(idata, odata))
    { 
        printf("Failed to run FFT%d!\n", nx);
        return 1;
    }
    timerc.Stop();
    printData(odata, nx * n_batch, nx);

    printf(" Overall time: %.6lf \n", timerc.GetElapsedTime());
	verifyData(odata,result,nx * n_batch, n_batch);

    _aligned_free(result);

    return 0;
}

int
main(int argc, char *argv[])
{
#if VERIFY
	const int n_entries = 1024*2+2048+8192 ;
#else
	const int n_entries = 1024*1024*64;
#endif
    const int n_bytes = n_entries * sizeof(float2);

// Initialize device
    Runtime * _runtime = Runtime::getInstance();
    ProgramManager* _progMgr = _runtime->getProgramManager();
    BufferManager*  _bufMgr = _runtime->getBufferManager();
    DeviceManager*  _devMgr = _runtime->getDeviceManager();
    CounterManager*  _cntMgr = _runtime->getCounterManager();

    if (_devMgr->getSysDeviceNum() <= ATI_DEVICE_ID) {
        cerr<<"Cal device unavailable!"<<endl;
        return 1;
    }
    _devMgr->assignDevice(ATI_DEVICE_ID);

	float2 *data = (float2 *)_aligned_malloc(sizeof(float2) * n_entries, 4096);	
    generateTestData(data, n_entries, 8);

    testFFT(data, data,   8, n_entries / 8);
    testFFT(data, data,  16, n_entries / 16);
    testFFT(data, data,  32, n_entries / 32);
    testFFT(data, data,  64, n_entries / 64);
    testFFT(data, data, 256, n_entries / 256);
    testFFT(data, data, 512, n_entries / 512);
    testFFT(data, data, 1024, n_entries / 1024);

    _aligned_free(data);

    return 0;

}
