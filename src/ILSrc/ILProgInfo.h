#ifndef _AMDSPL_CALPASS_H_
#define _AMDSPL_CALPASS_H_

#include <string>
#include <vector>

namespace amdspl
{
    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \enum ConstUsage
    //!
    //! \brief Enum showing usage of different constant arguments.
    //! The usage is needed for Address translation implementation.
    //! Only two extra constants are needed in new runtime 
    //! are streamshape and buffershape for AT.
    //! 
    ////////////////////////////////////////////////////////////////////////////////

    enum ConstUsage
    {
        //! \brief User constants.
        CONST_USER_PARAM,

        //! \brief Stream dimensions.
        CONST_STREAMSHAPE,

        //! \brief Buffer dimensions.
        CONST_BUFFERSHAPE,

        //! \brief Reduction factor used in the kernel
        CONST_REDUCTIONFACTOR,

        //! \brief Pitch of buffer. Required for 2D-Scatter implementation
        CONST_BUFFERPITCH,

        //! \brief force 32-bit size enum
        CONST_FORCE_DWORD    = 0x7fffffff
    };

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \struct ArgumentDesc
    //!
    //! \brief Structure to contain the usage of input parameter and 
    //! its associated parameter.
    //! Index shows for which stream argument we need the constsnt.
    //! 
    ////////////////////////////////////////////////////////////////////////////////

    struct ArgumentDesc
    {
        inline ArgumentDesc(int index, int usage, int type = 0);

        //! \brief data showing argument index for different arguments.
        int Index;
    };

    inline
    ArgumentDesc::ArgumentDesc(int index, int usage, int type)
    {
        Index = index;
    };

    typedef std::vector<ArgumentDesc> ArgDesc;

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \class Pass
    //!
    //! \brief Contain the metadata and backend specific Kernel program.
    //! 
    //! Metadata constains information for number of inputs, outputs, constants.
    //! 
    ////////////////////////////////////////////////////////////////////////////////

    class ILProgInfo 
    {
        public:
            ILProgInfo(const char* name);
            ILProgInfo& image(const char* image);
            ILProgInfo& constArray(int constArrayNum);
            ILProgInfo& constant(int constantNum);
            ILProgInfo& input(int inputNum);
            ILProgInfo& output(int outputNum);
            ILProgInfo& scatter(int scatterNum);

            ~ILProgInfo();

        public:

            //! \brief Name of the pass. This information is used
            //! for avoiding creation of CALProgram again and again.
            const char* Name;
            
            //! \brief Generated device specific assembly
            const char* Image;

            //! \brief The number of constant array 
            unsigned int ConstArrayNum;

            //! \brief The number of constants
            unsigned int ConstantNum;

            //! \brief The number of input stream.
            unsigned int InputNum;

            //! \brief The number of output stream
            unsigned int OutputNum;

            //! \brief The number of scatter output stream
            unsigned int ScatterNum;
    };
}

#endif
