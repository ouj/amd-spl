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
    //! \enum InputType
    //!
    //! \brief Enum showing different input types
    //! 
    ////////////////////////////////////////////////////////////////////////////////

    enum InputType
    {
        //! \brief Gather array
        INPUT_GATHER = 0,

        //! \brief Normal stream
        INPUT_STREAM,

        //! \brief force 32-bit size enum
        INPUT_FORCE_DWORD    = 0x7fffffff
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

        //! \brief Usage needed for different extra constant and struct support
        int Usage;

        //! \brief Type needed to differenciate between gather and normal streams
        // Brook semantics for stream resizing are different for gather and normal stream
        int Type;
    };

    inline
    ArgumentDesc::ArgumentDesc(int index, int usage, int type)
    {
        Index = index;
        Usage = usage;
        Type = type;
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

    class Pass 
    {
        public:

            Pass(const Pass& p);
            Pass(const char* name);
            Pass& operator=(const Pass& p);
            Pass& image(const char* image);
            Pass& constArray(int argumentIndex, int usage);
            Pass& constant(int argumentIndex, ConstUsage usage);
            Pass& input(int argumentIndex, int usage, InputType type = INPUT_GATHER);
            Pass& output(int argumentIndex, int usgae);
            Pass& scatter(int argumentIndex, int usage);

            ~Pass();

        public:

            //! \brief Name of the pass. This information is used
            //! for avoiding creation of CALProgram again and again.
            const char* Name;
            
            //! \brief Generated device specific assembly
            const char* Image;

            //! \brief Metadata of all the constant arrays.
            ArgDesc* ConstArrays;

            //! \brief Metadata of all the constants.
            ArgDesc* Constants;

            //! \brief Metadata of all the input streams.
            ArgDesc* Inputs;

            //! \brief Metadata of all the output streams.
            ArgDesc* Outputs;

            //! \brief Metadata of all the Scatter outputs
            ArgDesc* Scatters;

    };
}

#endif
