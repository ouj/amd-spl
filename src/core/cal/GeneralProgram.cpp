//////////////////////////////////////////////////////////////////////////
//!
//!	\file       GeneralProgram.cpp
//!	\date       11:5:2008   16:43
//!	\author     Jiawei Ou
//!	
//!	\brief      Contains definition of GeneralProgram class.
//!
//////////////////////////////////////////////////////////////////////////
#include "GeneralProgram.h"
#include "RuntimeDefs.h"

using namespace amdspl::core::cal;

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
            //! \brief	Construct a GeneralProgram object.
            //!
            //////////////////////////////////////////////////////////////////////////
            GeneralProgram::GeneralProgram(Device *device) : Program(device)
            {
                memset(&domain, 0, sizeof(CALdomain));
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Destructor
            //!
            //! \brief	Destroy the GeneralProgram object.
            //!
            //////////////////////////////////////////////////////////////////////////
            GeneralProgram::~GeneralProgram(void)
            {
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \param	exeInfo
            //! \return	bool
            //!
            //! \brief	Set the execution information of the program. For general 
            //!         program, it is cal domain. For compute program, it is 
            //!         execution grid information.
            //!
            //////////////////////////////////////////////////////////////////////////
            void GeneralProgram::setExeInfo(const ProgExeInfo &exeInfo)
            {
                domain.x = exeInfo.domain.x;
                domain.y = exeInfo.domain.y;
                domain.width = exeInfo.domain.z;
                domain.height = exeInfo.domain.w;
            }

            //////////////////////////////////////////////////////////////////////////
            //!
            //! \return	Event* The event of the execution.
            //!
            //! \brief	Execute the program.
            //!
            //////////////////////////////////////////////////////////////////////////
            Event*  GeneralProgram::run()
            {
                CALevent execEvent;
                CALcontext ctx = _device->getContext();

                syncConstBuffers();

                waitEvents();

                CALresult result = calCtxRunProgram(&execEvent, ctx, _func, &domain);
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
            }
        }
    }
}
