#ifndef AMDSPL_FFT_H_
#define AMDSPL_FFT_H_

/************************************************************************//*!
 *  \file   SplFFT.h
 *  \author Terence Wu
 *  \date   Aug 3 2009
 *
 *  \brief  FFT interface declarations
 *
 **************************************************************************/

#include "SplDefs.h"
#include "RuntimeDefs.h"
#include <vector>

using namespace amdspl::core::cal;

namespace amdspl
{
/************************************************************************//*!
 *  
 *  \brief Namespace of FFT
 *
 **************************************************************************/
    namespace fft
    {

        /****************************************************************//*!
         *  
         *  \brief FFT Flags 
         *
         ******************************************************************/
        typedef enum FFTflag_t {
            FFT_FLAG_FORWARD = 0x00,    //!< Forward FFT (default flag)
            FFT_FLAG_BACKWARD = 0x01,   //!< Backword FFT
            FFT_FLAG_GPU_BUFFER = 0x02  //!< Use SPL Buffer as input and output
        } FFTflag;
        
        class SPL_EXPORT FFTplan
        {
        public:
            FFTplan(void);
            ~FFTplan(void);

            SPL_RESULT init_1d(int nx, int batch, FFTflag flag = FFT_FLAG_FORWARD);
            
            SPL_RESULT execute(float2 * idata, float2 * odata);
        //    SPL_RESULT execute(Buffer * iobuf);

        private:
        //    SPL_RESULT  setupKernel(Program* &pprog, int nx, FFTflag flag);
            SPL_RESULT  init_1d_cpu();
            SPL_RESULT  init_1d_gpu();
            SPL_RESULT  init();

            SPL_RESULT  dataInput(float2 * data, Buffer * gBuf, int kernelIdx, uint4 * transParam=NULL);
            SPL_RESULT  dataOutput(float2 *data, Buffer * gBuf, int kernelIdx, uint4 * transParam=NULL);

            void        unloadAllProgram();
            void        getTransParam(int n, int direction, uint4 * transParam);

            FFTflag         _flag;
            int             _nx;
            int             _batch;

            //! \brief Resource size when using CPU context FFT.
            int4            _res_size_cpu;

            Runtime*        _runtime;
            ProgramManager* _progMgr;
            BufferManager*  _bufMgr;
            DeviceManager*  _devMgr;
            CounterManager*  _cntMgr;

            //! \brief GPU Program pool 
            vector<Program*>     _fftProgX;
            //! \brief Execute Info pool, correspond to the Program pool.
            vector<ProgExeInfo*> _exeInfoX;

        };

    }
}

#endif