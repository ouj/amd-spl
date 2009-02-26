//
//
//
//  @ Project : AMD-SPL
//  @ File Name : ProgramInfo.h
//  @ Date : 2009/2/9
//  @ Author : Jiawei Ou
//
//


#if !defined(_PROGRAMINFO_H)
#define _PROGRAMINFO_H
#include <string>

using namespace std;

namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            template <int outputsT, int inputsT = 0, int constantsT = 0, bool globalsT = false> 
            class ProgramInfo
            {
            public:
                ProgramInfo(const char* ID, const char* source)
                {
                    this->source = source;
                    this->Id = ID;
                }
                enum para
                {
                    outputs = outputsT,
                    inputs = inputsT,
                    constants = constantsT,
                    global = globalsT
                };

                inline const char* getSource() const
                {
                    return source.c_str();
                }

                inline const char* getID() const
                {
                    return Id;
                }

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
                string source;
                const char* Id;
            };
        }
    }
}

#endif  //_PROGRAMINFO_H
