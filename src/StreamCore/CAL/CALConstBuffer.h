#ifndef _AMDSPL_CALCONSTBUFFER_H_
#define _AMDSPL_CALCONSTBUFFER_H_
#include "cal.h"
#include "CALBuffer.h"
namespace amdspl
{
    class CalDevice;

    class CalConstBuffer : public CalBuffer
    {
    public:
        CalConstBuffer(unsigned int* dimensions, CalDevice* device, CALformat format);
        ~CalConstBuffer(void);

        void setConstant(void* data, CALformat format, unsigned int count = 1);
        bool setDataToBuffer();
    private:
        //! \brief CAL creates a buffer of multiple constants. 
        // _data points to the corresponding CPU array.
        unsigned char* _data;

        //! \brief number of bytes in _data
        unsigned int _nBytes;
    };
}
#endif