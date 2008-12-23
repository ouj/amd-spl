#include "CALProgramMgr.h"
#include "ILPrograms.h"
#include "CommonDefs.h"
#include "CALProgram.h"

namespace amdspl
{
    CalProgramMgr::CalProgramMgr(CalDevice *device) : _device(device)
    {
        _programs.resize(ILPRGROGRAMS_NUM, NULL);
    }

    CalProgramMgr::~CalProgramMgr(void)
    {
        for (unsigned int i = 0; i < ILPRGROGRAMS_NUM; i++)
        {
            SAFE_DELETE(_programs[i]);
        }
    }

    const CalProgram* CalProgramMgr::GetProgram(enum ILPROGRAMS_INDEX idx)
    {
        if (_programs[idx] == NULL)
        {
            CalProgram *program = new CalProgram(ILInfoFuncs[idx](), _device);
            if(!program->initialize())
            {
                SAFE_DELETE(program);
                return NULL;
            }
            _programs[idx] = program;
        }
        return _programs[idx];
    };
}

