#ifndef AMDSPL_GENERAL_PROGRAM_H
#define AMDSPL_GENERAL_PROGRAM_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file       GeneralProgram.h
//!	\date       11:5:2008   16:29
//!	\author     Jiawei Ou
//!	
//!	\brief      Contains declaration of GeneralProgram class.
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
            //! \brief     GeneralProgExeInfo class contains the 
            //!             execution information (cal domain) of a program.
            //!	
            //!	\author     Jiawei Ou
            //!
            //////////////////////////////////////////////////////////////////////////
            class SPL_EXPORT GeneralProgExeInfo : public ProgExeInfo
            {
            public:
                uint4   domain;

                GeneralProgExeInfo(uint4 domain)
                {
                    this->domain = domain;
                };
            };
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief      GeneralProgram is derived from Program class. It contains
            //!             execution logic of ps style Program.
            //! \warning    Not Thread Safe
            //!	
            //!	\author     Jiawei Ou
            //!
            //////////////////////////////////////////////////////////////////////////
            class SPL_EXPORT GeneralProgram : public Program
            {
            public:
                GeneralProgram(Device *device);
                virtual ~GeneralProgram(void);
                virtual void    setExeInfo(const ProgExeInfo &exeInfo);
                virtual Event*  run();
            private:
                CALdomain domain;
            };
        }
    }
}
#endif // AMDSPL_GENERAL_PROGRAM_H
