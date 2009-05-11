#ifndef AMDSPL_COMPUTE_PROGRAM_H
#define AMDSPL_COMPUTE_PROGRAM_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file       ComputeProgram.h
//!	\date       11:5:2008   16:44
//!	\author     Jiawei Ou
//!	
//!	\brief      Contains declaration of ComputeProgram class.
//!
//////////////////////////////////////////////////////////////////////////
#include "Program.h"
#include "SplDefs.h"

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief      GeneralProgram is derived from Program class. It contains
            //!             execution logic of cs style Program.
            //! \warning    Not thread safe.
            //!	
            //!	\author     Jiawei Ou
            //!
            //////////////////////////////////////////////////////////////////////////
            class ComputeProgram : public Program
            {
            public:
                ComputeProgram(Device *device);
                ~ComputeProgram(void);

                virtual void    setExeInfo(const ProgExeInfo &exeInfo);
                virtual Event*  run();
            private:
                CALprogramGrid  _pg;
            };
        }
    }
}

#endif // AMDSPL_COMPUTE_PROGRAM_H
