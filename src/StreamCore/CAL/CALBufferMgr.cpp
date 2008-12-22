#include "CALBase.h"
#include "CALBufferMgr.h"
#include "CALBuffer.h"
#include "CALConstBuffer.h"
#include "CALDevice.h"
#include "Utility.h"

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Shader to resize a stream with given resizeFactor
//!
////////////////////////////////////////////////////////////////////////////////
static const char resize_stream_shader[] = 
"il_ps_2_0\n"
"dcl_input_position_interp(linear_noperspective) v0.xy__\n"
"dcl_output_generic o0\n"
"dcl_cb cb0[5]\n"
"dcl_resource_id(0)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
"ftoi r0.xy__, v0.xyxx\n"
"imad r0.x___, r0.y, cb0[4].x, r0.x\n"
"ixor r0._y__, r0.x, cb0[3].x\n"
"; l0 = (-0.000000f -0.000000f -0.000000f -0.000000f)\n"
"dcl_literal l0, 0x80000000, 0x80000000, 0x80000000, 0x80000000\n"
"and r0._y__, r0.y, l0\n"
"imax r0.__z_, r0.x, r0.x_neg(xyzw)\n"
"imax r1.xy__, cb0[3].xyxx, cb0[3].xyxx_neg(xyzw)\n"
"udiv r0.__z_, r0.z, r1.x\n"
"inegate r0.___w, r0.z\n"
"cmov_logical r0._y__, r0.y, r0.w, r0.z\n"
"imax r0.__z_, r0.y, r0.y_neg(xyzw)\n"
"udiv r0.__z_, r0.z, r1.y\n"
"inegate r0.___w, r0.z\n"
"ixor r1.x___, r0.y, cb0[3].y\n"
"; l1 = (-0.000000f -0.000000f -0.000000f -0.000000f)\n"
"dcl_literal l1, 0x80000000, 0x80000000, 0x80000000, 0x80000000\n"
"and r1.x___, r1.x, l1\n"
"cmov_logical r0.__z_, r1.x, r0.w, r0.z\n"
"imul r0.___w, r0.z, cb0[3].y\n"
"itof r1.__z_, r0.z\n"
"iadd r0.__z_, r0.y, r0.w_neg(xyzw)\n"
"imul r0._y__, r0.y, cb0[3].x\n"
"itof r1._y__, r0.z\n"
"iadd r0.x___, r0.x, r0.y_neg(xyzw)\n"
"itof r1.x___, r0.x\n"
"div_zeroop(infinity) r0.xyz_, r1.xyzx, cb0[0].xyzx\n"
"ftoi r0.xyz_, r0.xyzx\n"
"imul r0._yz_, r0.zzyz, cb0[1].x\n"
"imad r0._y__, r0.y, cb0[1].y, r0.z\n"
"iadd r0.x___, r0.y, r0.x\n"
"ixor r0._y__, r0.x, cb0[2].x\n"
"; l2 = (-0.000000f -0.000000f -0.000000f -0.000000f)\n"
"dcl_literal l2, 0x80000000, 0x80000000, 0x80000000, 0x80000000\n"
"and r0._y__, r0.y, l2\n"
"imax r0.__z_, r0.x, r0.x_neg(xyzw)\n"
"imax r0.___w, cb0[2].x, cb0[2].x_neg(xyzw)\n"
"udiv r0.__z_, r0.z, r0.w\n"
"inegate r0.___w, r0.z\n"
"cmov_logical r0._y__, r0.y, r0.w, r0.z\n"
"imul r0.__z_, r0.y, cb0[2].x\n"
"itof r0._y__, r0.y\n"
"iadd r0.x___, r0.x, r0.z_neg(xyzw)\n"
"itof r0.x___, r0.x\n"
"; l3 = (0.500000f 0.000000f 0.500000f 0.000000f)\n"
"dcl_literal l3, 0x3F000000, 0x00000000, 0x3F000000, 0x00000000\n"
"add r0.x_z_, r0.xxyx, l3\n"
"sample_resource(0)_sampler(0) o0, r0.xzxx\n"
"ret_dyn\n"
"end\n";

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Copy shader to copy from a stream to another.
//!
////////////////////////////////////////////////////////////////////////////////
static const char domain_copy_shader[] = 
"il_ps_2_0\n"
"dcl_input_position_interp(linear_noperspective) v0.xy__\n"
"dcl_output_generic o0\n"
"dcl_cb cb0[1]\n"
"dcl_resource_id(0)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
"add r0.xy__, v0.xyxx, cb0[0].xyxx\n"
"sample_resource(0)_sampler(0) o0, r0.xyxx\n"
"ret_dyn\n"
"end\n"
;

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Copy shader to copy from a stream with AT to another stream
//! with AT or non AT.
//!
////////////////////////////////////////////////////////////////////////////////
static const char domainAT_copy_shader[] = 
"il_ps_2_0\n"
"dcl_input_position_interp(linear_noperspective) v0.xy__\n"
"dcl_output_generic o0\n"
"dcl_cb cb0[7]\n"
"dcl_resource_id(0)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n"
"ftoi r0.xy__, v0.xyxx\n"
"imad r0.x___, r0.y, cb0[6].x, r0.x\n"
"ixor r0._y__, r0.x, cb0[5].x\n"
"imax r0.__z_, r0.x, r0.x_neg(xyzw)\n"
"imax r1.xy__, cb0[5].xyxx, cb0[5].xyxx_neg(xyzw)\n"
"udiv r0.__z_, r0.z, r1.x\n"
"inegate r0.___w, r0.z\n"
"; l0 = (-0.000000f -0.000000f -0.000000f -0.000000f)\n"
"dcl_literal l0, 0x80000000, 0x80000000, 0x80000000, 0x80000000\n"
"and r0._y__, r0.y, l0\n"
"cmov_logical r0._y__, r0.y, r0.w, r0.z\n"
"imul r0.__z_, r0.y, cb0[5].x\n"
"iadd r0.x___, r0.x, r0.z_neg(xyzw)\n"
"ixor r1.x___, r0.y, cb0[5].y\n"
"imax r1.__z_, r0.y, r0.y_neg(xyzw)\n"
"udiv r1._y__, r1.z, r1.y\n"
"inegate r1.__z_, r1.y\n"
"; l1 = (-0.000000f -0.000000f -0.000000f -0.000000f)\n"
"dcl_literal l1, 0x80000000, 0x80000000, 0x80000000, 0x80000000\n"
"and r1.x___, r1.x, l1\n"
"cmov_logical r0.___w, r1.x, r1.z, r1.y\n"
"imul r1.x___, r0.w, cb0[5].y\n"
"iadd r0.__z_, r0.y, r1.x_neg(xyzw)\n"
"ilt r0._y__, r0.x, cb0[3].x\n"
"ilt r1.x___, cb0[4].x, r0.x\n"
"ior r0._y__, r0.y, r1.x\n"
"; l2 = (0.000000f 0.000000f 0.000000f 0.000000f)\n"
"dcl_literal l2, 0x00000001, 0x00000001, 0x00000001, 0x00000001\n"
"and r0._y__, r0.y, l2\n"
"ilt r1.x___, r0.z, cb0[3].y\n"
"ilt r1._y__, cb0[4].y, r0.z\n"
"ior r1.x___, r1.x, r1.y\n"
"; l3 = (0.000000f 0.000000f 0.000000f 0.000000f)\n"
"dcl_literal l3, 0x00000001, 0x00000001, 0x00000001, 0x00000001\n"
"and r1.x___, r1.x, l3\n"
"ilt r1._y__, r0.w, cb0[3].z\n"
"ilt r1.__z_, cb0[4].z, r0.w\n"
"ior r1._y__, r1.y, r1.z\n"
"; l4 = (0.000000f 0.000000f 0.000000f 0.000000f)\n"
"dcl_literal l4, 0x00000001, 0x00000001, 0x00000001, 0x00000001\n"
"and r1._y__, r1.y, l4\n"
"iadd r0._y__, r0.y, r1.x\n"
"iadd r0._y__, r0.y, r1.y\n"
"if_logicalnz r0.y\n"
"    ; l5 = (-1.#QNAN0f -1.#QNAN0f -1.#QNAN0f -1.#QNAN0f)\n"
"    dcl_literal l5, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF\n"
"    discard_logicalnz l5\n"
"endif\n"
"iadd r0.xyz_, r0.xzwx, cb0[3].xyzx_neg(xyzw)\n"
"iadd r0.xyz_, r0.xyzx, cb0[2].xyzx\n"
"imul r0._yz_, r0.zzyz, cb0[0].x\n"
"imad r0._y__, r0.y, cb0[0].y, r0.z\n"
"iadd r0.x___, r0.y, r0.x\n"
"ixor r0._y__, r0.x, cb0[1].x\n"
"imax r0.__z_, r0.x, r0.x_neg(xyzw)\n"
"imax r0.___w, cb0[1].x, cb0[1].x_neg(xyzw)\n"
"udiv r0.__z_, r0.z, r0.w\n"
"inegate r0.___w, r0.z\n"
"; l6 = (-0.000000f -0.000000f -0.000000f -0.000000f)\n"
"dcl_literal l6, 0x80000000, 0x80000000, 0x80000000, 0x80000000\n"
"and r0._y__, r0.y, l6\n"
"cmov_logical r0._y__, r0.y, r0.w, r0.z\n"
"imul r0.__z_, r0.y, cb0[1].x\n"
"iadd r0.x___, r0.x, r0.z_neg(xyzw)\n"
"itof r0.x___, r0.x\n"
"; l7 = (0.500000f 0.500000f 0.500000f 0.500000f)\n"
"dcl_literal l7, 0x3F000000, 0x3F000000, 0x3F000000, 0x3F000000\n"
"add r0.x___, r0.x, l7\n"
"itof r0._y__, r0.y\n"
"; l8 = (0.500000f 0.500000f 0.500000f 0.500000f)\n"
"dcl_literal l8, 0x3F000000, 0x3F000000, 0x3F000000, 0x3F000000\n"
"add r0.__z_, r0.y, l8\n"
"sample_resource(0)_sampler(0) r0, r0.xzxx\n"
"mov o0, r0\n"
"ret_dyn\n"
"end\n";

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Kernel descriptor for the copy shaders
//!
////////////////////////////////////////////////////////////////////////////////
//static brook::KernelDesc copy_shader_desc = brook::KernelDesc()
//.technique(brook::Technique()
//           .pass(brook::Pass("__domain_copy_shader")
//           .image( domain_copy_shader )
//           .constant(1, brook::CONST_USER_PARAM)
//           .input(0, 0)
//           .output(2,0)
//           )
//           )
//           .technique(brook::Technique()
//           .pass(brook::Pass("__domainAT_copy_shader")
//           .image(domainAT_copy_shader)
//           .constant(1, brook::CONST_USER_PARAM)
//           .constant(1, brook::CONST_USER_PARAM)
//           .constant(1, brook::CONST_USER_PARAM)
//           .constant(1, brook::CONST_USER_PARAM)
//           .constant(1, brook::CONST_USER_PARAM)
//           .constant(1, brook::CONST_USER_PARAM)
//           .constant(1, brook::CONST_USER_PARAM)
//           .input(0, 0)
//           .output(2, 0)
//           )
//           )
//           ;
//
//const brook::KernelDesc* CALBufferMgr::_copy_shader_desc = &copy_shader_desc;


////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Kernel descriptor to resize stream
//!
////////////////////////////////////////////////////////////////////////////////
//static brook::KernelDesc resize_shader_desc = brook::KernelDesc()
//.technique(brook::Technique()
//           .pass(brook::Pass("__resize_stream_shader")
//           .image(resize_stream_shader)
//           .constant(1, brook::CONST_USER_PARAM)
//           .constant(1, brook::CONST_USER_PARAM)
//           .constant(1, brook::CONST_USER_PARAM)
//           .constant(1, brook::CONST_USER_PARAM)
//           .constant(1, brook::CONST_USER_PARAM)
//           .input(0, 0)
//           .output(2,0)
//           )
//           );
//
//const brook::KernelDesc* CALBufferMgr::_resize_shader_desc = &resize_shader_desc;

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Constructor
//!
//! \param device The device associated to a bufferMgr
//!
////////////////////////////////////////////////////////////////////////////////

CalBufferMgr::CalBufferMgr(CalDevice* device) :  _device(device)
{
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Method to create backend spefic buffers using CALBuffer.
//!
//! \param stream The associated stream
//! \return Pointer to the newly created buffer
//!
////////////////////////////////////////////////////////////////////////////////

CalBuffer*
CalBufferMgr::createBuffer(unsigned short rank, unsigned int* dimensions, CALformat calFormat)
{
    // Check if double precision is supported on the underlying hardware
    CALdeviceattribs attrib = _device->getAttribs();
    CALdeviceinfo info = _device->getInfo();

    if(!attrib.doublePrecision)
    {
        if(calFormat == CAL_FORMAT_DOUBLE_1 || calFormat == CAL_FORMAT_DOUBLE_2)
        {
            //stream->setErrorCode(BR_ERROR_NOT_SUPPORTED);
            //stream->setErrorString("Stream Allocation : Double precision not supported " 
            //    "on underlying hardware\n");

            return NULL;
        }
    }

    if(rank == 1 && dimensions[0] > info.maxResource1DWidth)
    {
        //stream->setErrorCode(BR_ERROR_NOT_SUPPORTED);
        //stream->setErrorString("Stream Allocation : This dimension not supported on undelying"
        //    "hardware\n");

        return NULL;
    }
    else if(rank == 2 && (dimensions[0] > info.maxResource2DWidth || 
        dimensions[1] > info.maxResource2DHeight))
    {
        //stream->setErrorCode(BR_ERROR_NOT_SUPPORTED);
        //stream->setErrorString("Stream Allocation : This dimension not supported on undelying"
        //    "hardware\n");

        return NULL;
    }

    return new CalBuffer(rank, dimensions, calFormat, 
        BUFFER_LOCAL, 0, _device);
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Implementation of Stream.read()
//!
//! Contains logic to get CALParity using tile by tile copy
//!
//! \param stream StreamImpl Class
//! \param ptr Application pointer to copy
//!
////////////////////////////////////////////////////////////////////////////////

void
CalBufferMgr::setBufferData(CalBuffer* stream, const void* ptr)
{
    //unsigned int bufferCount = stream->getBufferCount();

    //if(!stream->flush())
    //{
    //    stream->setErrorCode(BR_ERROR_READ);
    //    stream->setErrorString("Stream Read : Could not flush previous events\n");

    //    return;
    //}

    //for(unsigned int bufNum = 0; bufNum < bufferCount; ++bufNum)
    //{
    //    CALBuffer* buffer = static_cast<CALBuffer*>(stream->getBuffer(bufNum));

    //    unsigned int rank = buffer->getRank();
    //    unsigned int* dimension = buffer->getDimensions();
    //    CALformat format = buffer->getFormat();

    //    // create a host resource to use DMA for data transfer
    //    CALBuffer* tmpBuffer = _createHostBuffer(rank, dimension, format);

    //    unsigned int startPoint[MaxRank];
    //    memset(startPoint, 0, MaxRank * sizeof(unsigned int));

    //    if(tmpBuffer != NULL)
    //    {
    //        // Set Host resource data with the given application pointer
    //        unsigned int pitch = 0;
    //        void* tmpPtr = tmpBuffer->getBufferPointerCPU(pitch);

    //        if(!tmpPtr)
    //        {
    //            stream->setErrorCode(BR_ERROR_READ);
    //            stream->setErrorString("Stream Read : Failed to map resource\n");
    //        }

    //        stream->setData(tmpPtr, ptr, bufNum, pitch, startPoint, dimension);
    //        tmpBuffer->freeBufferPointerCPU();

    //        //DMA transfer
    //        CALevent* copyEvent = _getCopyEvent();
    //        if(!buffer->copyAsync(tmpBuffer, copyEvent))
    //        {
    //            stream->setErrorCode(BR_ERROR_READ);
    //            stream->setErrorString("Stream Read : Failed to Initiate DMA\n");
    //        }

    //        //Set the associated event on local and host buffer
    //        buffer->setCopyEvent(copyEvent);
    //        tmpBuffer->setCopyEvent(copyEvent);
    //    }
    //    else
    //    {
    //        //Start tile by tile copying
    //        unsigned int tiledDimension[MaxRank];

    //        unsigned int i = 0;
    //        for(; i < rank; ++i)
    //        {
    //            tiledDimension[i] = (dimension[i] < TileSize) ? dimension[i] : TileSize;
    //        }
    //        for(; i < MaxRank; ++i)
    //        {
    //            tiledDimension[i] = 1;
    //        }

    //        // Create a host resource of tile size
    //        tmpBuffer = _createHostBuffer(rank, tiledDimension, format);

    //        if(tmpBuffer == NULL)
    //        {
    //            stream->setErrorCode(BR_ERROR_READ);
    //            stream->setErrorString("Stream Read : Failed to create host resource \n");

    //            return;
    //        }

    //        unsigned int* tiledStartPoint = new unsigned int[rank];
    //        memset(tiledStartPoint, 0, rank * sizeof(unsigned int));

    //        BRformat format = stream->getDataFormat(bufNum);

    //        // We need to create a temporary stream to use copy method
    //        StreamImpl* tmpStream = new StreamImpl(rank, tiledDimension, &format, 1, _device);
    //        tmpStream->setBuffer(tmpBuffer, 0);

    //        unsigned int width = dimension[0];
    //        unsigned int height = (rank == 1) ? 1 : dimension[1];

    //        while(startPoint[1] < height)
    //        {
    //            startPoint[0] = 0;
    //            tiledDimension[0] = (width < TileSize) ? width : TileSize;

    //            while(startPoint[0] < width)
    //            {
    //                // Set Host resource data with the given application pointer
    //                unsigned int pitch = 0;
    //                void* tmpPtr = tmpBuffer->getBufferPointerCPU(pitch);

    //                if(!tmpPtr)
    //                {
    //                    stream->setErrorCode(BR_ERROR_READ);
    //                    stream->setErrorString("Stream Read : Failed to map tiled resource\n");
    //                }

    //                stream->setData(tmpPtr, ptr, bufNum, pitch, startPoint, tiledDimension);
    //                tmpBuffer->freeBufferPointerCPU();

    //                // invoke copy shader
    //                bool success = tmpStream->copy(tmpStream, tiledStartPoint, stream, startPoint, 
    //                    tiledDimension, false, 0, bufNum);

    //                if(!success)
    //                {
    //                    stream->setErrorCode(BR_ERROR_READ);
    //                    stream->setErrorString("Stream Read : Failed to copy data from tiled host resource to "
    //                        " stream\n");

    //                    return;
    //                }

    //                tmpBuffer->waitInputEvent();

    //                // Move to next tile in horizontal direction
    //                startPoint[0] = startPoint[0] + tiledDimension[0];
    //                tiledDimension[0] = ((width - startPoint[0]) < TileSize) ? 
    //                    (width - startPoint[0]) : TileSize;

    //            }

    //            // Move to next tile in vertical direction
    //            startPoint[1] = startPoint[1] + tiledDimension[1];
    //            tiledDimension[1] = ((height - startPoint[1]) < TileSize) ? 
    //                (height - startPoint[1]) : TileSize;
    //        }

    //        delete[] tiledStartPoint;
    //        delete tmpStream;
    //    }
    //}

    //stream->copyDataToTree();
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Implementation of Stream.write()
//!
//! Contains logic to get CALParity using tile by tile copy
//!
//! \param stream StreamImpl Class
//! \param ptr Application pointer to copy
//!
////////////////////////////////////////////////////////////////////////////////

void
CalBufferMgr::getBufferData(CalBuffer* stream, void* ptr)
{
    //unsigned int bufferCount = stream->getBufferCount();
    //stream->copyDataFromTree();

    //for(unsigned int bufNum = 0; bufNum < bufferCount; ++bufNum)
    //{
    //    CALBuffer* buffer = static_cast<CALBuffer*>(stream->getBuffer(bufNum));

    //    if(buffer == NULL)
    //    {
    //        stream->setErrorCode(BR_ERROR_WRITE);
    //        stream->setErrorString("Stream Write : Uninitialized stream\n");
    //        return;
    //    }

    //    // Wait for all the events
    //    //No need to wait for input event as stream write is not going to modify buffer data
    //    buffer->waitCopyEvent();
    //    buffer->waitOutputEvent();

    //    unsigned int rank = buffer->getRank();
    //    unsigned int* dimension = buffer->getDimensions();
    //    CALformat format = buffer->getFormat();

    //    // create a host resource to use DMA for data transfer
    //    CALBuffer* tmpBuffer = _createHostBuffer(rank, dimension, format);

    //    unsigned int startPoint[MaxRank];
    //    memset(startPoint, 0, MaxRank * sizeof(unsigned int));

    //    if(tmpBuffer != NULL)
    //    {
    //        CALevent* copyEvent = _getCopyEvent();
    //        if(!tmpBuffer->copyAsync(buffer, copyEvent))
    //        {
    //            stream->setErrorCode(BR_ERROR_WRITE);
    //            stream->setErrorString("Stream Write : Failed to Initiate DMA\n");
    //        }

    //        //Wait for the event to finish
    //        buffer->setCopyEvent(copyEvent);
    //        buffer->waitCopyEvent();

    //        // Get Host resource data in the given application pointer
    //        unsigned int pitch = 0;
    //        void* tmpPtr = tmpBuffer->getBufferPointerCPU(pitch);

    //        if(!tmpPtr)
    //        {
    //            stream->setErrorCode(BR_ERROR_WRITE);
    //            stream->setErrorString("Stream Write : Failed to map resource\n");
    //        }

    //        stream->getData(tmpPtr, ptr, bufNum, pitch, startPoint, dimension);
    //        tmpBuffer->freeBufferPointerCPU();
    //    }
    //    else
    //    {
    //        //Start tile by tile copying
    //        unsigned int tiledDimension[MaxRank];
    //        unsigned int i = 0;
    //        for(; i < rank; ++i)
    //        {
    //            tiledDimension[i] = (dimension[i] < TileSize) ? dimension[i] : TileSize;
    //        }
    //        for(; i < MaxRank; ++i)
    //        {
    //            tiledDimension[i] = 1;
    //        }

    //        // Create a host resource of tile size
    //        tmpBuffer = _createHostBuffer(rank, tiledDimension, format);
    //        if(tmpBuffer == NULL)
    //        {
    //            stream->setErrorCode(BR_ERROR_WRITE);
    //            stream->setErrorString("Stream Write : Failed to create host resource \n");

    //            return;
    //        }

    //        unsigned int* tiledStartPoint = new unsigned int[rank];
    //        memset(tiledStartPoint, 0, rank * sizeof(unsigned int));

    //        BRformat format = stream->getDataFormat(bufNum);

    //        // We need to create a temporary stream to use copy method
    //        StreamImpl* tmpStream = new StreamImpl(rank, tiledDimension, &format, 1, _device);
    //        tmpStream->setBuffer(tmpBuffer, 0);

    //        unsigned int width = dimension[0];
    //        unsigned int height = (rank == 1) ? 1 : dimension[1];

    //        while(startPoint[1] < height)
    //        {
    //            startPoint[0] = 0;
    //            tiledDimension[0] = (width < TileSize) ? width : TileSize;

    //            while(startPoint[0] < width)
    //            {
    //                // invoke copy shader
    //                bool success = tmpStream->copy(stream, startPoint, tmpStream, tiledStartPoint, 
    //                    tiledDimension, false, bufNum, 0);

    //                if(!success)
    //                {
    //                    stream->setErrorCode(BR_ERROR_READ);
    //                    stream->setErrorString("Stream Write : Failed to copy data from tiled host "
    //                        "resource to stream\n");

    //                    return;
    //                }

    //                buffer->waitInputEvent();

    //                // Get Host resource data in the given application pointer
    //                unsigned int pitch = 0;
    //                void* tmpPtr = tmpBuffer->getBufferPointerCPU(pitch);

    //                if(!tmpPtr)
    //                {
    //                    stream->setErrorCode(BR_ERROR_WRITE);
    //                    stream->setErrorString("Stream Write : Failed to map tiled resource\n");
    //                }

    //                stream->getData(tmpPtr, ptr, bufNum, pitch, startPoint, tiledDimension);
    //                tmpBuffer->freeBufferPointerCPU();

    //                // Move to next tile in horizontal direction
    //                startPoint[0] = startPoint[0] + tiledDimension[0];
    //                tiledDimension[0] = ((width - startPoint[0]) < TileSize) ? 
    //                    (width - startPoint[0]) : TileSize;

    //            }

    //            // Move to next tile in vertical direction
    //            startPoint[1] = startPoint[1] + tiledDimension[1];
    //            tiledDimension[1] = ((height - startPoint[1]) < TileSize) ? 
    //                (height - startPoint[1]) : TileSize;
    //        }

    //        delete[] tiledStartPoint;
    //        delete tmpStream;
    //    }
    //}
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Method to create CAL host buffers using CALBuffer.
//!
//! Uses a host resource cache to avoid allocation/ de-allocation
//!
//! \return Pointer to the newly created host buffer
//!
////////////////////////////////////////////////////////////////////////////////

CalBuffer* 
CalBufferMgr::createHostBuffer(unsigned short rank, unsigned int* dimensions,
                                const CALformat & format)
{
    CalBuffer* tmpBuffer = new CalBuffer(rank, dimensions, format, BUFFER_HOST,
        CAL_RESALLOC_CACHEABLE, _device);

    // Look into cache if a free resource exist of the same size
    unsigned int i = 0;
    CalBuffer* sameSizedBuffer = NULL;
    for(i = 0; i < _hostBufferCache.size(); ++i)
    {
        // Is size same?
        if(*_hostBufferCache[i] == *tmpBuffer)
        {
            // if size is same look if it is being used for another data transfer
            sameSizedBuffer = _hostBufferCache[i];
            CALevent copyEvent = sameSizedBuffer->getCopyEvent();
            CALevent inputEvent = sameSizedBuffer->getInputEvent();
            CALevent outputEvent = sameSizedBuffer->getOutputEvent();

            if(copyEvent == inputEvent == outputEvent == 0)
            {
                delete tmpBuffer;
                return sameSizedBuffer;
            }
        }
    }

    // Ceate if no free buffer in cache and push it in the cache
    if(!tmpBuffer->initialize())
    {
        // If same size buffer exist in cache. Wait for its events to finish
        // and return the same
        if(sameSizedBuffer)
        {
            sameSizedBuffer->waitCopyEvent();
            sameSizedBuffer->waitInputEvent();
            sameSizedBuffer->waitOutputEvent();

            delete tmpBuffer;

            return sameSizedBuffer;
        }
        else
        {
            // If there is no same sized buffer, wait for all the events 
            // associated to host resouces to finish and delete them.
            for(i = 0; i < _hostBufferCache.size(); ++i)
            {
                CalBuffer* buffer = _hostBufferCache[i];
                buffer->waitCopyEvent();
                buffer->waitInputEvent();
                buffer->waitOutputEvent();

                delete buffer;
            }

            _hostBufferCache.clear();

            // Try again to allocate resouce after deallocating all the resources
            if(!tmpBuffer->initialize())
            {
                delete tmpBuffer;

                return NULL;
            }
        }
    }

    // Keep it in a cache after creation
    _hostBufferCache.push_back(tmpBuffer);

    return tmpBuffer;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Method to clear used constant cache.
//!
//! This is used to avoid the case when same constant buffer is retuned for a
//! kernel invocation
//!
//!
////////////////////////////////////////////////////////////////////////////////

void
CalBufferMgr::clearUsedConstCache()
{
    _usedConstBuffers.clear();
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Method to create CALConstBuffer
//!
//! Uses a constant buffer cache to avoid allocation/ de-allocation
//!
//! \return Pointer to the newly created constant buffer
//!
////////////////////////////////////////////////////////////////////////////////

CalConstBuffer*
CalBufferMgr::createConstBuffer(unsigned int numConstants, CALformat calFormat)
{
    CALdeviceinfo info = _device->getInfo();
    if(numConstants > info.maxResource1DWidth)
    {
        return NULL;
    }

    // Try to use a nearest power 2 dimension so that we can 
    // cover cases when we need < 64 constant in a kernel(very likely)
    // with single constant buffer
    unsigned int size = amdspl::utils::ceilPow(numConstants);
    if(size == 0)
    {
        return NULL;
    }

    size = (size > 64) ? size : 64;

    unsigned int dimensions[] = {size};
    CalConstBuffer* tmpBuffer;

    tmpBuffer = new CalConstBuffer(dimensions, _device, calFormat);

    // Look into cache if a free resource exist of the same size
    unsigned int i = 0;
    CalConstBuffer* sameSizedBuffer = NULL;
    for(i = 0; i < _constBufferCache.size(); ++i)
    {
        // Is the size same?
        if(*_constBufferCache[i] == *tmpBuffer)
        {
            unsigned int j = 0;
            for(j = 0; j < _usedConstBuffers.size(); ++j)
            {
                if(_constBufferCache[i] == _usedConstBuffers[j])
                {
                    break;
                }
            }

            if(j == _usedConstBuffers.size())
            {
                sameSizedBuffer = _constBufferCache[i];
                CALevent inputEvent = sameSizedBuffer->getInputEvent();

                // If it is free, return it.
                if(inputEvent == 0)
                {
                    delete tmpBuffer;
                    sameSizedBuffer->reuse();
                    _usedConstBuffers.push_back(sameSizedBuffer);

                    return sameSizedBuffer;
                }
            }
        }
    }

    // Ceate if no free buffer in cache and push it in the cache
    if(!tmpBuffer->initialize())
    {
        // If same size buffer exist in cache. Wait for its events to finish
        // and return the same
        if(sameSizedBuffer)
        {
            sameSizedBuffer->waitInputEvent();
            delete tmpBuffer;
            sameSizedBuffer->reuse();
            _usedConstBuffers.push_back(sameSizedBuffer);

            return sameSizedBuffer;
        }
        else
        {
            // If there is no same sized buffer, wait for all the events 
            // associated to host resouces to finish and delete them.
            for(i = 0; i < _constBufferCache.size(); ++i)
            {
                CalConstBuffer* buffer = _constBufferCache[i];
                buffer->waitInputEvent();

                delete buffer;
            }

            _constBufferCache.clear();

            // Try again to allocate resouce after deallocating all the resources
            if(!tmpBuffer->initialize())
            {
                SET_ERROR("Failed to create host cal resource for constant buffer\n");
                delete tmpBuffer;

                return NULL;
            }
        }
    }

    _constBufferCache.push_back(tmpBuffer);
    _usedConstBuffers.push_back(tmpBuffer);

    return tmpBuffer;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief 
//! return backend specific resize kernel, used in input stream resize 
//! to match their size with output streams
//!
////////////////////////////////////////////////////////////////////////////////

//const brook::KernelDesc*
//CalBufferMgr::getResizeShaderDesc()
//{
//    return _resize_shader_desc;
//}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief return backend specific copy kernel, used in tile by tile 
//! copying and domain implementation
//!
////////////////////////////////////////////////////////////////////////////////

//const brook::KernelDesc*
//CalBufferMgr::getCopyShaderDesc()
//{
//    return _copy_shader_desc;
//}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Destructor
//! Delete data from caches for host buffer and constant buffer
//!
////////////////////////////////////////////////////////////////////////////////

CalBufferMgr::~CalBufferMgr()
{
    // Destroy all the host side and constant buffers available in cache
    for(unsigned int i = 0; i < _hostBufferCache.size(); ++i)
    {
        delete _hostBufferCache[i];
    }

    _hostBufferCache.clear();

    for(unsigned int i = 0; i < _constBufferCache.size(); ++i)
    {
        delete _constBufferCache[i];
    }

    for(unsigned int i = 0; i < _copyEvents.size(); ++i)
    {
        delete _copyEvents[i];
    }

}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Return an event that is not being used
//!
////////////////////////////////////////////////////////////////////////////////

CALevent* 
CalBufferMgr::_getCopyEvent()
{
    // Look for a free event in the cache
    unsigned int i;
    for(i = 0; i < _copyEvents.size(); ++i)
    {
        if(*_copyEvents[i] == 0)
        {
            return _copyEvents[i];
        }
    }

    // Create if not found
    CALevent* event = new CALevent();
    *event = 0;
    _copyEvents.push_back(event);

    return event;
}

void CalBufferMgr::destroyBuffer(CalBuffer *buffer)
{

}