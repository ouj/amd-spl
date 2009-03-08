#if !defined(_PROGRAMINFO_H)
#define _PROGRAMINFO_H
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

using namespace std;

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            //////////////////////////////////////////////////////////////////////////
            //!
            //! \tparam outputsT    Template parameter of output register number.
            //! \tparam inputsT     Template parameter of input register number.
            //! \tparam constantsT  Template parameter of constant register number.
            //! \tparam globalT     Template parameter indicate whether there is a 
            //!                     global register.
            //!
            //! \brief	ProgramInfo class contains information of a IL program. 
            //! \warning Not thread safe.
            //!
            //////////////////////////////////////////////////////////////////////////
            template <int outputsT, int inputsT = 0, int constantsT = 0, bool globalsT = false> 
            class ProgramInfo
            {
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
                    this->source = source;
                    this->Id = ID;
                }

                //////////////////////////////////////////////////////////////////////////
                //!
                //! \brief  Parameter information of the program. These enumerate values
                //!         are initialized by template parameter in compile-time.
                //!
                //////////////////////////////////////////////////////////////////////////
                enum para
                {
                    //! \brief	output register number.
                    outputs = outputsT,
                    //! \brief	input register number.
                    inputs = inputsT,
                    //! \brief	constant register number.
                    constants = constantsT,
                    //! \brief	boolean value indicate whether there is a global buffer.
                    global = globalsT
                };

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
