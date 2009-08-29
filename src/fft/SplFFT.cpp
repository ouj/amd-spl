/************************************************************************//*!
 *  \file   SplFFT.cpp
 *  \author Terence Wu
 *  \date   Aug 3 2009
 *
 *  \brief  FFT implementation
 *
 **************************************************************************/

#include "SplFFT.h"
#include "Utility.h"
#include "il/fft_il.h"
#include "il/ifft_il.h"
#include "il/preprocess_il.h"

#include "Timer.h"

using namespace amdspl::core::cal;

namespace amdspl
{
    namespace fft
    {
        
        FFTplan::FFTplan(void) 
        {
            _runtime = 0;
            _progMgr = 0;
            _bufMgr = 0;
            _devMgr = 0;

            _fftProgX.clear();
            _exeInfoX.clear();
        }

        FFTplan::~FFTplan(void) 
        {
            unloadAllProgram();
        }

        void FFTplan::unloadAllProgram() 
        {
            for (int i = 0; i < _fftProgX.size() ; i++) {
                if (_fftProgX[i])
                {
                    _progMgr->unloadProgram(_fftProgX[i]);
                    _fftProgX[i] = NULL;
                }
            }
            _fftProgX.clear();

            for (int i = 0; i < _exeInfoX.size() ; i++) {
                if (_exeInfoX[i])
                {
                    delete _exeInfoX[i];
                    _exeInfoX[i] = NULL;
                }
            }
            _exeInfoX.clear();
        }

        SPL_RESULT FFTplan::init_1d(int nx, int batch, FFTflag flag)
        {
            SPL_RESULT result;

            if (result = init()) {
                return result;
            }

            _flag = flag;
            _nx = nx;
            _batch = batch;

            if (flag & ~FFT_FLAG_GPU_BUFFER) {
                result = init_1d_gpu();
            }else{
                result = init_1d_cpu();
            }

            if (result) {
                unloadAllProgram();
            }
            return result;
        }

        SPL_RESULT FFTplan::init_1d_gpu()
        {
            ///TODO: implement GPU context interface
            return SPL_RESULT_INVALID_ARGUMENT;
        }

        SPL_RESULT FFTplan::init_1d_cpu() 
        {
            ProgramInfo proginfo;
            Program * prog;
            ProgExeInfo * exeinfo;

            int paddedSize = _nx * _batch / 2;
            int width, height;
            const int maxWidth = _devMgr->getDefaultDevice()->getInfo().maxResource2DWidth;
            const int maxHeight = _devMgr->getDefaultDevice()->getInfo().maxResource2DHeight;
            int stride = (int)_devMgr->getDefaultDevice()->getAttribs().pitch_alignment * 2;
    
            if (_batch % 2) {
                return SPL_RESULT_INVALID_ARGUMENT;
            }

            // Caculate the sizes of GPU resources
            for (width = maxWidth; width > 0; width -= stride) {
                if (paddedSize % width == 0) break;
            }
            if (width < stride) {
                return SPL_RESULT_INVALID_ARGUMENT;
            }
            height = paddedSize / width;
            if (height > maxHeight) {
                return SPL_RESULT_INVALID_ARGUMENT;
            }
            _res_size_cpu.x = width;
            _res_size_cpu.y = height;
            _res_size_cpu.z = 8192;
            _res_size_cpu.w = (paddedSize + _res_size_cpu.z -1) / _res_size_cpu.z;

	        proginfo = ProgramInfo("input@SplFFT", _fft_input_cs_transXY_source_).inputs(2).constants(1).hasGlobal().isCompute();
	        prog = _progMgr->loadProgram(proginfo, _devMgr->getDefaultDevice());
            if (!prog) {
                return SPL_RESULT_PROGRAM_ERROR;
            }
            _fftProgX.push_back(prog);
            exeinfo = new ComputeProgExeInfo(0, uint3(64, 1, 1), uint3(_nx * _batch / 4 / 64, 1, 1));
            _exeInfoX.push_back(exeinfo);

            switch (_nx)
            {
            case 8:
                proginfo = ProgramInfo("FFT8", _fft8_tomo_fft_source_).hasGlobal().isCompute();
                prog = _progMgr->loadProgram(proginfo, _devMgr->getDefaultDevice());
                if (!prog) {
                    return SPL_RESULT_PROGRAM_ERROR;
                }
                _fftProgX.push_back(prog);
                exeinfo = new ComputeProgExeInfo(0, uint3(64, 1, 1), uint3((_batch + 127) / 2 / 64, 1, 1));
                _exeInfoX.push_back(exeinfo);

                break;
            case 16:
                proginfo = ProgramInfo("FFT16", _fft16_tomo_fft_source_).hasGlobal().isCompute();
                prog = _progMgr->loadProgram(proginfo, _devMgr->getDefaultDevice());
                if (!prog) {
                    return SPL_RESULT_PROGRAM_ERROR;
                }
                _fftProgX.push_back(prog);
                exeinfo = new ComputeProgExeInfo(0, uint3(64, 1, 1), uint3((_batch + 127) / 2 / 64, 1, 1));
                _exeInfoX.push_back(exeinfo); 

                break;
            case 32:
                proginfo = ProgramInfo("FFT32", _fft32_tomo_fft_source_).hasGlobal().isCompute();
                prog = _progMgr->loadProgram(proginfo, _devMgr->getDefaultDevice());
                if (!prog) {
                    return SPL_RESULT_PROGRAM_ERROR;
                }
                _fftProgX.push_back(prog);
                exeinfo = new ComputeProgExeInfo(0, uint3(64, 1, 1), uint3((_batch + 127) / 2 / 64, 1, 1));
                _exeInfoX.push_back(exeinfo); 

                break;
            case 64:
                proginfo = ProgramInfo("FFT64", _fft64_tomo_fft_source_).hasGlobal().isCompute();
                prog = _progMgr->loadProgram(proginfo, _devMgr->getDefaultDevice());
                if (!prog) {
                    return SPL_RESULT_PROGRAM_ERROR;
                }
                _fftProgX.push_back(prog);
                exeinfo = new ComputeProgExeInfo(0, uint3(64, 1, 1), uint3((_batch + 15) / 2 / 8, 1, 1));
                _exeInfoX.push_back(exeinfo); 

                break;
            case 256:
                proginfo = ProgramInfo("FFT256", _fft256_tomo_fft_source_).hasGlobal().isCompute();
                prog = _progMgr->loadProgram(proginfo, _devMgr->getDefaultDevice());
                if (!prog) {
                    return SPL_RESULT_PROGRAM_ERROR;
                }
                _fftProgX.push_back(prog);
                exeinfo = new ComputeProgExeInfo(0, uint3(64, 1, 1), uint3((_batch + 7) / 2 / 4, 1, 1));
                _exeInfoX.push_back(exeinfo); 

                break;
            case 512:
                proginfo = ProgramInfo("FFT512", _fft512_tomo_fft_source_).hasGlobal().isCompute();
                prog = _progMgr->loadProgram(proginfo, _devMgr->getDefaultDevice());
                if (!prog) {
                    return SPL_RESULT_PROGRAM_ERROR;
                }
                _fftProgX.push_back(prog);
                exeinfo = new ComputeProgExeInfo(0, uint3(64, 1, 1), uint3((_batch + 7) / 2 / 4, 1, 1));
                _exeInfoX.push_back(exeinfo); 

                break;
            case 1024:
                proginfo = ProgramInfo("FFT1024", _fft1024_tomo_fft_source_).hasGlobal().isCompute();
                prog = _progMgr->loadProgram(proginfo, _devMgr->getDefaultDevice());
                if (!prog) {
                    return SPL_RESULT_PROGRAM_ERROR;
                }
                _fftProgX.push_back(prog);
                exeinfo = new ComputeProgExeInfo(0, uint3(64, 1, 1), uint3((_batch + 3) / 2 / 2, 1, 1));
                _exeInfoX.push_back(exeinfo); 

                break;
            default:
                return SPL_RESULT_INVALID_ARGUMENT;
            }

	        proginfo = ProgramInfo("output@SplFFT", _fft_output_cs_transXY_source_).inputs(1).constants(1).hasGlobal().isCompute();
	        prog = _progMgr->loadProgram(proginfo, _devMgr->getDefaultDevice());
            if (!prog) {
                return SPL_RESULT_PROGRAM_ERROR;
            }
            _fftProgX.push_back(prog);
            exeinfo = new ComputeProgExeInfo(0, uint3(64, 1, 1), uint3(_nx * _batch / 4 / 64, 1, 1));
            _exeInfoX.push_back(exeinfo);

            return SPL_RESULT_OK;
        }

        void FFTplan::getTransParam(int n, int direction, uint4 * transParam) 
        {
            switch (n * 2 + direction) 
            {
            case 8 *2:
            case 8 *2+1:
	            transParam[0] = uint4(3, 6, 0, 0); //(8, 64, 1, )
	            transParam[1] = uint4(0x00000007, 0x0000003F, 0x00000000, 0); //(8, 64, 1, )
                break;
            case 16 *2:
            case 16 *2+1:
	            transParam[0] = uint4(4, 6, 0, 0); //(16, 64, 1, )
	            transParam[1] = uint4(0x0000000F, 0x0000003F, 0x00000000, 0);
                break;
            case 32 *2:
	            transParam[0] = uint4(5, 6, 0, 0); //(32, 64, 1, )
	            transParam[1] = uint4(0x0000001F, 0x0000003F, 0x00000000, 0);
                break;
            case 32 *2+1:
	            transParam[0] = uint4(0, 0, 0, 0); //(32, 64, 1, )
	            transParam[1] = uint4(0x00000000, 0x00000000, 0x00000000, 0);
                break;
            case 64 *2:
            case 64 *2+1:
	            transParam[0] = uint4(3, 3, 3, 0); //(8, 8, 8, )
	            transParam[1] = uint4(0x00000007, 0x00000007, 0x00000007, 0);
                break;
            case 256 *2:
            case 256 *2+1:
	            transParam[0] = uint4(4, 2, 4, 0); //(16, 4, 16, )
	            transParam[1] = uint4(0x0000000F, 0x00000003, 0x0000000F, 0);
                break;
            case 512 *2:
	            transParam[0] = uint4(5, 2, 4, 0); //(32, 4, 16, )
	            transParam[1] = uint4(0x0000001F, 0x00000003, 0x0000000F, 0);
                break;
            case 512 *2+1:
	            transParam[0] = uint4(5, 4, 0, 0); //(32, 16, 1, )
	            transParam[1] = uint4(0x0000001F, 0x0000000F, 0x00000000, 0);
                break;
            case 1024 *2:
	            transParam[0] = uint4(5, 1, 5, 0); //(32, 2, 32, )
	            transParam[1] = uint4(0x0000001F, 0x00000001, 0x0000001F, 0);
                break;
            case 1024 *2+1:
	            transParam[0] = uint4(5, 5, 0, 0); //(32, 32, 1, )
	            transParam[1] = uint4(0x0000001F, 0x0000001F, 0x00000000, 0);
                break;
            }
        }

        SPL_RESULT FFTplan::execute(amdspl::float2 *idata, amdspl::float2 *odata)
        {
            if (_flag & ~FFT_FLAG_GPU_BUFFER)
                return SPL_RESULT_BUFFER_ERROR;

            if (_fftProgX.size()<3 || !_fftProgX[0])
                return SPL_RESULT_PROGRAM_ERROR;

            //amdspl::utils::Timer timerc;
	        const unsigned int paddedSize = _nx * _batch / 2;

	        uint4 transParam[2];

            Buffer* gBuf = 
                _bufMgr->createLocalBuffer(_devMgr->getDefaultDevice(), CAL_FORMAT_FLOAT32_4,
                        _res_size_cpu.z, _res_size_cpu.w, CAL_RESALLOC_GLOBAL_BUFFER);
            if (!gBuf)
            {
                LOG_ERROR("Failed to create global buffer!\n");
                return SPL_RESULT_BUFFER_ERROR;
            }
            getTransParam(_nx, 0, transParam);
	        dataInput(idata, gBuf, 0, transParam);

	        // ============== compute ================
            Program * _fftProg = _fftProgX[1];

	        _fftProg->bindGlobal(gBuf);
            _fftProg->setExeInfo(*_exeInfoX[1]);

	        //timerc.Start();
            Event *e = _fftProg->run();
            if (!e) {
                return SPL_RESULT_PROGRAM_ERROR;
            }
	        e->waitEvent();
	        //timerc.Stop();

            getTransParam(_nx, 1, transParam);
	        dataOutput(odata, gBuf, 2, transParam);

	        // ============== clean up ==================

	        _fftProg->unbindAll();
	        _bufMgr->destroyBuffer(gBuf);

            //printf("  FFT Time: %lf\n", timerc.GetElapsedTime());

            return SPL_RESULT_OK;
        }

/*        SPL_RESULT FFTplan::execute(Buffer *iobuf) 
        {
            if (!(_flag & ~FFT_FLAG_GPU_BUFFER)) 
                return SPL_RESULT_BUFFER_ERROR;

            if (!iobuf) 
                return SPL_RESULT_BUFFER_ERROR;

            if (_fftProgX.size()<=0 || !_fftProgX[0])
                return SPL_RESULT_PROGRAM_ERROR;

            _fftProgX[0]->bindGlobal(iobuf);
            _fftProgX[0]->setExeInfo(*_exeInfoX[0]);

            Event *e = _fftProgX[0]->run();
            if (!e) {
                return SPL_RESULT_PROGRAM_ERROR;
            }
            e->waitEvent();
            _fftProgX[0]->unbindAll();

            return SPL_RESULT_OK;
        }
*/
/*        SPL_RESULT FFTplan::setupKernel(Program *&pprog, int nx, FFTflag flag) 
        {
            ProgramInfo proginfo;
            switch (nx)
            {
            case 8:
                proginfo = ProgramInfo("FFT8", _fft8_tomo_fft_source_).hasGlobal().isCompute();
                break;
            default:
                return SPL_RESULT_INVALID_ARGUMENT;
            }
            
            // Load IL Programs
            pprog = _progMgr->loadProgram(proginfo, _devMgr->getDefaultDevice());
            if (!pprog)
                return SPL_RESULT_PROGRAM_ERROR;

            return SPL_RESULT_OK;
        }
*/
        SPL_RESULT FFTplan::init()
        {
            if (_devMgr && _progMgr && _bufMgr && _runtime)
                return SPL_RESULT_OK;

            // Setup SPL environment;
            _runtime = Runtime::getInstance();
            if(!_runtime) {
                return SPL_RESULT_NOT_INITIALIZED;
            }

            _devMgr = _runtime->getDeviceManager();
            _progMgr = _runtime->getProgramManager();
            _bufMgr = _runtime->getBufferManager();
            _cntMgr = _runtime->getCounterManager(); 
            assert(_devMgr && _progMgr && _bufMgr);

            if (!_devMgr->getDefaultDevice())
            {
                return SPL_RESULT_NOT_INITIALIZED;
            }

            return SPL_RESULT_OK;
        }

        SPL_RESULT FFTplan::dataInput(float2 * data, Buffer * gBuf, int kernelIdx, uint4 * transParam)
        {
            const unsigned int pinned_mask = (4096-1);
	        // ============== input =====================

	        bool pinned_flag_1 = false; 
	        float *pinned_input_1 = NULL;
	        bool pinned_flag_2 = false; 
	        float *pinned_input_2 = NULL;

            int paddedSize =  _nx * _batch / 2;
            Program * _fftInputProg = _fftProgX[kernelIdx];

	        if (((uintptr_t)data) & pinned_mask) {
		        pinned_input_1 = (float *)_aligned_malloc(sizeof(float2) * paddedSize, pinned_mask + 1);
		        LOG_TRACE("Generated new pinned buffer 1 \n");
		        memcpy(pinned_input_1, data, sizeof(float2) * paddedSize);
		        pinned_flag_1 = true;
	        } else {
		        pinned_input_1 = (float *)data;
	        }

	        if (((uintptr_t)(data + paddedSize)) & pinned_mask) {
		        pinned_input_2 = (float *)_aligned_malloc(sizeof(float2) * paddedSize, pinned_mask + 1);
		        LOG_TRACE("Generated new pinned buffer 2 \n");
		        memcpy(pinned_input_2, data + paddedSize, sizeof(float2) * paddedSize);
		        pinned_flag_2 = true;
	        } else {
		        pinned_input_2 = (float *)(data + paddedSize);
	        }

	        Buffer * iBuf1 = 
		        _bufMgr->createPinnedBuffer(_devMgr->getDefaultDevice(), CAL_FORMAT_FLOAT32_4, 
                        _res_size_cpu.x/2, _res_size_cpu.y, pinned_input_1);
	        assert(iBuf1);

	        Buffer * iBuf2 = 
		        _bufMgr->createPinnedBuffer(_devMgr->getDefaultDevice(), CAL_FORMAT_FLOAT32_4, 
                        _res_size_cpu.x/2, _res_size_cpu.y, pinned_input_2);
	        assert(iBuf2);

	        ConstBuffer* cBuf = _bufMgr->getConstBuffer(3);
	        uint4 cdata(_res_size_cpu.x, _res_size_cpu.y, paddedSize/2);
	        assert(cBuf->setConstant(0, &cdata));
	        assert(cBuf->setConstant(1, transParam));
	        assert(cBuf->setConstant(2, transParam + 1));

	        _fftInputProg->bindInput(iBuf1, 0);
	        _fftInputProg->bindInput(iBuf2, 1);
	        _fftInputProg->bindConstant(cBuf, 0);
	        _fftInputProg->bindGlobal(gBuf);

            ComputeProgExeInfo inputExeInfo(0, uint3(64, 1, 1), uint3(paddedSize / 2 / 64, 1, 1));
            _fftInputProg->setExeInfo(inputExeInfo);

            Event *e = _fftInputProg->run();
            if (!e) {
                return SPL_RESULT_PROGRAM_ERROR;
            }
	        e->waitEvent();
	        _fftInputProg->unbindAll();

	        _bufMgr->releaseConstBuffer(cBuf);
	        _bufMgr->destroyBuffer(iBuf1);
	        _bufMgr->destroyBuffer(iBuf2);

	        if (pinned_flag_1) {
		        _aligned_free(pinned_input_1);
	        }
	        if (pinned_flag_2) {
		        _aligned_free(pinned_input_2);
	        }

	        return SPL_RESULT_OK;
        }

        SPL_RESULT FFTplan::dataOutput(float2 * data, Buffer * gBuf, int kernelIdx, uint4 * transParam)
        {
            const unsigned int pinned_mask = (4096-1);
	        // ============== output ==================

	        bool pinned_flag_out = false; 
	        float *pinned_out = NULL;

            int paddedSize =  _nx * _batch / 2;
            Program * _fftOutputProg = _fftProgX[kernelIdx];

	        if (((uintptr_t)data) & pinned_mask) {
		        pinned_out = (float *)_aligned_malloc(sizeof(float4) * paddedSize, pinned_mask + 1);
		        printf("generated new pinned output buffer \n");
		        pinned_flag_out = true;
	        } else {
		        pinned_out = (float *)data;
	        }

            Buffer* ogBuf = 
                _bufMgr->createPinnedBuffer(_devMgr->getDefaultDevice(), CAL_FORMAT_FLOAT32_4,
                        _res_size_cpu.x, _res_size_cpu.y, pinned_out);
            if (!ogBuf)
            {
                LOG_ERROR("Failed to create global buffer!\n");
                return SPL_RESULT_BUFFER_ERROR;
            }

	        ConstBuffer* cBuf = _bufMgr->getConstBuffer(3);
	        uint4 cdata(_res_size_cpu.z, _res_size_cpu.w, paddedSize/2);
	        assert(cBuf->setConstant(0, &cdata));
	        assert(cBuf->setConstant(1, transParam));
	        assert(cBuf->setConstant(2, transParam + 1));

	        Event *e = NULL;
	        _fftOutputProg->bindInput(gBuf, 0);
	        _fftOutputProg->bindConstant(cBuf, 0);
	        _fftOutputProg->bindGlobal(ogBuf);

	        ComputeProgExeInfo outputExeInfo(0, uint3(64, 1, 1), uint3(paddedSize / 2 / 64, 1, 1));
	        _fftOutputProg->setExeInfo(outputExeInfo);

	        e = _fftOutputProg->run();
            if (!e) {
                return SPL_RESULT_PROGRAM_ERROR;
            }
	        e->waitEvent();

	        _fftOutputProg->unbindAll();

	        if (pinned_flag_out) {
		        memcpy(data, pinned_out, sizeof(float4) * paddedSize);
		        _aligned_free(pinned_out);
	        }

	        _bufMgr->releaseConstBuffer(cBuf);
	        _bufMgr->destroyBuffer(ogBuf);

	        return SPL_RESULT_OK;
        }

    }
}
