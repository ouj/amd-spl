//////////////////////////////////////////////////////////////////////////
//!
//!	\file       ComputeProgram.cpp
//!	\date       11:5:2008   16:43
//!	\author     Jiawei Ou
//!	
//!	\brief      Contains definition of ComputeProgram class.
//!
//////////////////////////////////////////////////////////////////////////
#include "ComputeProgram.h"
#include "RuntimeDefs.h"
#include "cal_ext.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	device The pointer to the Device object this program 
            //!         associated to. 
            //! \return	Constructor
            //!
            //! \brief	Construct a ComputeProgram object.
            //!
            //////////////////////////////////////////////////////////////////////////
            ComputeProgram::ComputeProgram(Device *device) : Program(device)
            {
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy the ComputeProgram object.
            //!
            //////////////////////////////////////////////////////////////////////////
            ComputeProgram::~ComputeProgram(void)
            {
            }

            void ComputeProgram::setExeInfo(const ProgExeInfo &exeInfo)
            {
                const ComputeProgExeInfo cs_exeInfo = static_cast<const ComputeProgExeInfo&>(exeInfo);
                _pg.func = _func;
                _pg.flags = cs_exeInfo.flags;
                _pg.gridBlock.width = cs_exeInfo.gridBlock.x;
                _pg.gridBlock.height = cs_exeInfo.gridBlock.y;
                _pg.gridBlock.depth = cs_exeInfo.gridBlock.z;
                _pg.gridSize.width = cs_exeInfo.gridSize.x;
                _pg.gridSize.height = cs_exeInfo.gridSize.y;
                _pg.gridSize.depth = cs_exeInfo.gridSize.z;
            }

            Event* ComputeProgram::run()
            {
                static PFNCALCTXRUNPROGRAMGRID calCtxRunProgramGrid = 0;
                if (calCtxRunProgramGrid == 0)
                {
                    calExtGetProc((CALextproc*)&calCtxRunProgramGrid, CAL_EXT_COMPUTE_SHADER, "calCtxRunProgramGrid");
                    if (calCtxRunProgramGrid == 0)
                    {
                        LOG_ERROR("Error: Compute shader extension not found\n");
                        return false;
                    }
                }

                CALevent execEvent;
                CALcontext ctx = _device->getContext();

                syncConstBuffers();

                waitEvents();

                CALresult result = calCtxRunProgramGrid(&execEvent, ctx, &_pg);
                CHECK_CAL_RESULT_ERROR2(result, "Failed to execute program!\n");

                // Force a dispatch of kernel to the device.
                result = calCtxIsEventDone(ctx, execEvent);
                if (result == CAL_RESULT_ERROR)
                {
                    LOG_ERROR("Event error!\n");
                    return 0;
                }

                // Get an event from the event pool
                Event* e = 
                    Runtime::getInstance()->getProgramManager()->getEvent();

                e->set(execEvent, ctx);
                setEvents(e);

                return e;

                return NULL;
            }
        }
    }
}
