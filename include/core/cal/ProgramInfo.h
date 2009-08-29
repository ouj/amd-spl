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
#include <stdio.h>
#include <string>
#include <assert.h>
#include "SplDefs.h"
#include "CommonDefs.h"

using namespace std;

#define IL_KERNEL(...) #__VA_ARGS__ 
#define MAX_SOURCE_LENGTH (1024 * 1024 * 2)

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
                //! \return	Constructor
                //!
                //! \brief	Construct the ProgramInfo object.(Default Constructor)
                //!
                //////////////////////////////////////////////////////////////////////////
                ProgramInfo(void)
                {
                    _outputs = 0;
                    _inputs = 0;
                    _constants = 0;
                    _global = false;
                    _isCS = false;
                }

                //////////////////////////////////////////////////////////////////////////
                //!
                //! \param	pi ProgramInfo object to be copied.
                //! \return	Constructor
                //!
                //! \brief	Copy construct the ProgramInfo object.
                //!
                //////////////////////////////////////////////////////////////////////////
                ProgramInfo(const ProgramInfo& pi)
                {
                    _outputs = pi._outputs;
                    _inputs = pi._inputs;
                    _constants = pi._constants;
                    _global = pi._global;
                    _isCS = pi._isCS;

                    Id = pi.Id;
                    source = pi.source;
                }

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
                    if (strncmp(source, "file://", 7)==0) {
                        FILE * fp;
                        fopen_s(&fp, source + 7, "rb");
                        if (!fp) {
                            LOG_ERROR("File open error.");
                            assert(fp);
                        }

                        long len; 
                        char * buf;
                        fseek(fp, 0, SEEK_END); //go to end
                        len = ftell(fp); //get position at end (length)
                        fseek(fp, 0, SEEK_SET); //go to beg.

                        if (len > MAX_SOURCE_LENGTH) {
                            LOG_ERROR("Size exceeded maximum.");
                            assert(0);
                        }
                        buf = (char *)malloc(len); //malloc buffer
                        fread(buf, len, 1, fp); //read into buffer
                        fclose(fp);

                        this->source = buf;
                        free(buf);
                    }else{
                        this->source = source;
                    }
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
                    return Id.c_str();
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
                    return *this;
                }

            private:
                //! \brief	Stores the source string of the IL program.
                string source;
                //! \brief	Stores the program ID string.
                string Id;
            };
        }
    }
}

#endif  //_PROGRAMINFO_H
