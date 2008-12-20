/****************************************************************************

Copyright (c) 2008, Advanced Micro Devices, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of Advanced Micro Devices, Inc nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

****************************************************************************/


#include "KernelDesc.h"

namespace amdspl
{
    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Overloded copyConstructor
    //! \param pass the Pass object reference
    //!
    ////////////////////////////////////////////////////////////////////////////////

    Pass::Pass(const Pass& p)
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

    Pass&
    Pass::operator=(const Pass& p)
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

    Pass::Pass(const char* name) : Name(name), Image(NULL)
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

    Pass& Pass::image(const char* image)
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

    Pass& Pass::constArray(int argumentIndex, int size)
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

    Pass& Pass::constant(int argumentIndex, ConstUsage usage)
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

    Pass& Pass::input(int argumentIndex, int usage, InputType type)
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

    Pass& Pass::output(int argumentIndex, int usage)
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
    
    Pass& Pass::scatter(int argumentIndex, int usage)
    {
        Scatters->push_back(ArgumentDesc(argumentIndex, usage));

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Destructor.
    //!
    ////////////////////////////////////////////////////////////////////////////////

    Pass::~Pass()
    {
        delete ConstArrays;
        delete Constants;
        delete Inputs;
        delete Outputs;
        delete Scatters;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Overloded copyConstructor
    //! \param technique the Technique object reference
    //!
    ////////////////////////////////////////////////////////////////////////////////

    Technique::Technique(const amdspl::Technique& t)
    {
        Passes = new std::vector<Pass>;
        AddressTranslation = t.AddressTranslation;
        *Passes = *(t.Passes);
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Operator overloaded to provide support for the copy constructor
    //! \param technique the Technique object reference
    //!
    ////////////////////////////////////////////////////////////////////////////////

    Technique&
    Technique::operator=(const amdspl::Technique& t)
    {
        Passes = new std::vector<Pass>;
        AddressTranslation = t.AddressTranslation;
        *Passes = *(t.Passes);

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Constructor
    //!
    ////////////////////////////////////////////////////////////////////////////////

    Technique::Technique() : AddressTranslation(false)
    {
        Passes = new std::vector<Pass>;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Add a pass in technique
    //! \param Pass 
    //!
    ////////////////////////////////////////////////////////////////////////////////
    
    Technique& Technique::pass(Pass& p)
    {
        Passes->push_back(p);

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief set AddressTranslation property
    //!
    ////////////////////////////////////////////////////////////////////////////////
    
    Technique& Technique::addressTranslation()
    {
        AddressTranslation = true;

        return *this;
    }

    Technique::~Technique()
    {
        delete Passes;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Operator overloaded to provide support for the copy constructor
    //! \param kernelDesc the KernelDesc object reference
    //!
    ////////////////////////////////////////////////////////////////////////////////

    KernelDesc::KernelDesc(const KernelDesc& desc)
    {
        Techniques = new std::vector<Technique>;
        *Techniques = *(desc.Techniques);
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Operator overloaded to provide support for the copy constructor
    //! \param technique the Technique object reference
    //!
    ////////////////////////////////////////////////////////////////////////////////

    KernelDesc&
    KernelDesc::operator=(const KernelDesc& desc)
    {
        Techniques = new std::vector<Technique>;
        *Techniques = *(desc.Techniques);

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Constructor
    //!
    ////////////////////////////////////////////////////////////////////////////////

    KernelDesc::KernelDesc()
    {
        Techniques = new std::vector<Technique>;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Add a technique in KernelDesc
    //! \param Technique 
    //!
    ////////////////////////////////////////////////////////////////////////////////
    
    KernelDesc& KernelDesc::technique(Technique& t)
    {
        Techniques->push_back(t);

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \brief Destructor
    //!
    ////////////////////////////////////////////////////////////////////////////////

    KernelDesc::~KernelDesc()
    {
        delete Techniques;
    }
}
