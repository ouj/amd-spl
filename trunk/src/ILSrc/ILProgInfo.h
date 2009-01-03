#ifndef _AMDSPL_CALPASS_H_
#define _AMDSPL_CALPASS_H_

#include <string>
#include <vector>

namespace amdspl
{
    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \class Pass
    //!
    //! \brief Contain the metadata and backend specific Kernel program.
    //! 
    //! Metadata constains information for number of inputs, outputs, constants.
    //! 
    ////////////////////////////////////////////////////////////////////////////////

    template<unsigned int INPUT_NUM = 0, 
        unsigned int OUTPUT_NUM = 0, 
        unsigned int CONST_NUM = 0,
        unsigned int CONST_ARRAY_NUM = 0, 
        unsigned int SCATTER_NUM = 0>
    class ILParameters
    {
    public:
        enum{
            InputNum = INPUT_NUM,
            OutputNum = OUTPUT_NUM,
            ConstantNum = CONST_NUM,
            ConstArrayNum = CONST_ARRAY_NUM,
            ScatterNum = SCATTER_NUM
        };
    };
}

#endif
