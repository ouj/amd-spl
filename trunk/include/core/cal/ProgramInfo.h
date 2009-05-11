#ifndef AMDSPL_PROGRAMINFO_H
#define AMDSPL_PROGRAMINFO_H
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		ProgramInfo.h
//!	\date 		1:3:2009   14:53
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains the template declaration and definition of 
//!             ProgramInfo class.
//!
//////////////////////////////////////////////////////////////////////////
#include <string>
#include <assert.h>

using namespace std;

#define IL_KERNEL(...) #__VA_ARGS__ 

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \brief	ProgramInfo class contains information of a IL program. 
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            class ProgramInfo
            {
                friend class Program;
            public:
                //////////////////////////////////////////////////////////////////////////
                //!
                //! \param	ID      The program ID string.
                //! \param	source  The program source string.
                //! \return	Constructor
                //!
                //! \brief	Construct the ProgramInfo object.
                //!
                //////////////////////////////////////////////////////////////////////////
                ProgramInfo(const char* ID, const char* source)
                {
                    assert(ID);
                    assert(source);
                    this->source = source;
                    this->Id = ID;

                    _outputs = 0;
                    _inputs = 0;
                    _constants = 0;
                    _global = false;
                    _isCS = false;
                }

                unsigned int _outputs;
                unsigned int _inputs;
                unsigned int _constants;
                bool         _global;
                bool         _isCS; 

                //////////////////////////////////////////////////////////////////////////
                //!
                //! \return	const char* The source string of the IL program.
                //!
                //! \brief	Get the source string of the IL program.
                //!
                //////////////////////////////////////////////////////////////////////////
                inline const char* getSource() const
                {
                    return source.c_str();
                }

                //////////////////////////////////////////////////////////////////////////
                //!
                //! \return	const char* The program ID string.
                //!
                //! \brief	Get the program ID string.
                //!
                //////////////////////////////////////////////////////////////////////////
                inline const char* getID() const
                {
                    return Id;
                }

                //////////////////////////////////////////////////////////////////////////
                //!
                //! \param	token   The token string in the original IL source about to
                //!                 be replaced.
                //! \param	src     The src fragment to replace the token.
                //! \return	ProgramInfo&    The reference to the ProgramInfo object.
                //!
                //! \brief	Replace the a token with a source fragment. This methods try to
                //!         avoid writing similar IL programs.
                //!
                //////////////////////////////////////////////////////////////////////////
                ProgramInfo& replaceTkn(const char *token, const char *src)
                {
                    string t(token);
                    string::size_type pos = -1;
                    pos = source.find(t);
                    if (pos != string::npos)
                    {
                        source.replace(pos, t.size(), src);
                    }
                    return *this;
                };

                inline ProgramInfo& outputs(unsigned int outputs = 0)
                {
                    _outputs = outputs;
                    return *this;
                };

                inline ProgramInfo& inputs(unsigned int inputs = 0)
                {
                    _inputs = inputs;
                    return *this;
                };

                inline ProgramInfo& constants(unsigned int constants = 0)
                {
                    _constants = constants;
                    return *this;
                };

                inline ProgramInfo& hasGlobal()
                {
                    _global = true;
                    return *this;
                };

                inline ProgramInfo& isCompute()
                {
                    _isCS = true;
                }

            private:
                //! \brief	Stores the source string of the IL program.
                string source;
                //! \brief	Stores the program ID string.
                const char* Id;
            };
        }
    }
}

#endif  //_PROGRAMINFO_H
