#include "ILProgInfo.h"

namespace amdspl
{
    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Constructor.
    //! \param name Name of the pass.
    //!
    ////////////////////////////////////////////////////////////////////////////////

    ILProgInfo::ILProgInfo(const char* name) : Name(name), Image(NULL)
    {
        ConstArrayNum = 0;
        HasConstant = false;
        InputNum = 0;
        OutputNum = 0;
        ScatterNum = 0;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief  Set the location of image
    //! \param name Name of the pass.
    //!
    ////////////////////////////////////////////////////////////////////////////////

    ILProgInfo& ILProgInfo::image(const char* image)
    {
        if(image)
        {
            Image = image;
        }

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief  Set constant arrays metadata using argument index of the constant
    //!         and its size
    //! \param argumentIndex 
    //! \param size
    //!
    ////////////////////////////////////////////////////////////////////////////////

    ILProgInfo& ILProgInfo::constArray(int constArrayNum)
    {
        ConstArrayNum = constArrayNum;

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief  Set constant metadata using argument index of the constant
    //!         and its usage if it is an extra constant required for different
    //!         virtualization.
    //! \param argumentIndex 
    //! \param usage 
    //!
    ////////////////////////////////////////////////////////////////////////////////

    ILProgInfo& ILProgInfo::constant(bool hasConstant)
    {
        HasConstant = hasConstant;

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Input metadata information showing its argument index.
    //!         usage is 0 for now.
    //! \param argumentIndex 
    //! \param usage 
    //!
    ////////////////////////////////////////////////////////////////////////////////

    ILProgInfo& ILProgInfo::input(int inputNum)
    {
        InputNum = inputNum;

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Output metadata information showing its argument index.
    //!         usage is 0 for now.
    //! \param argumentIndex 
    //! \param usage 
    //!
    ////////////////////////////////////////////////////////////////////////////////

    ILProgInfo& ILProgInfo::output(int outputNum)
    {
        OutputNum = outputNum;

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Scatter metadata information showing its argument index.
    //!        usage is 0 for now.
    //! \param argumentIndex 
    //! \param usage 
    //!
    ////////////////////////////////////////////////////////////////////////////////
    
    ILProgInfo& ILProgInfo::scatter(int scatterNum)
    {
        ScatterNum = scatterNum;

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Destructor.
    //!
    ////////////////////////////////////////////////////////////////////////////////

    ILProgInfo::~ILProgInfo()
    {
    }
}
