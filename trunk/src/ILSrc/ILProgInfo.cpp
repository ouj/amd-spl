#include "ILProgInfo.h"

namespace amdspl
{
    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Overloded copyConstructor
    //! \param pass the Pass object reference
    //!
    ////////////////////////////////////////////////////////////////////////////////

    ILProgInfo::ILProgInfo(const ILProgInfo& p)
    {
        Name = p.Name;
        Image = p.Image;

        ConstArrays = new ArgDesc;
        Constants = new ArgDesc;
        Inputs = new ArgDesc;
        Outputs = new ArgDesc;
        Scatters = new ArgDesc;

        *ConstArrays = *(p.ConstArrays);
        *Constants = *(p.Constants);
        *Inputs = *(p.Inputs);
        *Outputs = *(p.Outputs);
        *Scatters = *(p.Scatters);
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Operator overloaded to provide support for the copy constructor
    //! \param pass the Pass object reference
    //!
    ////////////////////////////////////////////////////////////////////////////////

    ILProgInfo&
    ILProgInfo::operator=(const ILProgInfo& p)
    {
        Name = p.Name;
        Image = p.Image;

        ConstArrays = new ArgDesc;
        Constants = new ArgDesc;
        Inputs = new ArgDesc;
        Outputs = new ArgDesc;
        Scatters = new ArgDesc;

        *ConstArrays = *(p.ConstArrays);
        *Constants = *(p.Constants);
        *Inputs = *(p.Inputs);
        *Outputs = *(p.Outputs);
        *Scatters = *(p.Scatters);

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Constructor.
    //! \param name Name of the pass.
    //!
    ////////////////////////////////////////////////////////////////////////////////

    ILProgInfo::ILProgInfo(const char* name) : Name(name), Image(NULL)
    {
        ConstArrays = new ArgDesc;
        Constants = new ArgDesc;
        Inputs = new ArgDesc;
        Outputs = new ArgDesc;
        Scatters = new ArgDesc;
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

    ILProgInfo& ILProgInfo::constArray(int argumentIndex, int size)
    {
        ConstArrays->push_back(ArgumentDesc(argumentIndex, size));

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

    ILProgInfo& ILProgInfo::constant(int argumentIndex, ConstUsage usage)
    {
        Constants->push_back(ArgumentDesc(argumentIndex, usage));

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

    ILProgInfo& ILProgInfo::input(int argumentIndex, int usage, InputType type)
    {
        Inputs->push_back(ArgumentDesc(argumentIndex, usage, type));

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

    ILProgInfo& ILProgInfo::output(int argumentIndex, int usage)
    {
        Outputs->push_back(ArgumentDesc(argumentIndex, usage));

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
    
    ILProgInfo& ILProgInfo::scatter(int argumentIndex, int usage)
    {
        Scatters->push_back(ArgumentDesc(argumentIndex, usage));

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Destructor.
    //!
    ////////////////////////////////////////////////////////////////////////////////

    ILProgInfo::~ILProgInfo()
    {
        delete ConstArrays;
        delete Constants;
        delete Inputs;
        delete Outputs;
        delete Scatters;
    }
}
