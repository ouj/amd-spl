#ifndef _AMDSPL_CALPARAMETERS_H_
#define _AMDSPL_CALPARAMETERS_H_

#include <string>
#include <vector>

namespace amdspl
{
    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \class ILParaInfo
    //!
    //! \brief Contain the parameter information for specific IL program.
    //! 
    //! parameter information contains number of inputs, outputs, constants.
    //! 
    ////////////////////////////////////////////////////////////////////////////////

    template<unsigned int INPUT_NUM = 0, 
        unsigned int OUTPUT_NUM = 0, 
        unsigned int CONST_NUM = 0,
        unsigned int CONST_ARRAY_NUM = 0, 
        unsigned int SCATTER_NUM = 0>
    class ILParaInfo
    {
    public:
        enum{
            InputNum = INPUT_NUM,
            OutputNum = OUTPUT_NUM,
            ConstantNum = CONST_NUM,
            ConstArrayNum = CONST_ARRAY_NUM,
            ScatterNum = SCATTER_NUM
        };

        static const char* image;
    };
}

#endif
