#ifndef _AMDSPL_CALPROGMGR_
#define _AMDSPL_CALPROGMGR_

#include <vector>

namespace amdspl
{
    class CalDevice;
    class CalProgramMgr
    {
    public:
        CalProgramMgr(CalDevice *device);
        ~CalProgramMgr(void);

        //const CalProgram* GetProgram(enum ILPROGRAMS_INDEX idx); 
    private:
        //! \brief Device for which this BufferMgr works
        CalDevice* _device;

        //std::vector<CalProgram*> _programs;
    };
};

#endif