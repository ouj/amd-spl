#ifndef _AMDSPL_CALCONSTBUFFER_H_
#define _AMDSPL_CALCONSTBUFFER_H_
#include "cal.h"
#include "CALBuffer.h"
#include "Utility.h"
#include "VectorDataType.h"

namespace amdspl
{
    class CalDevice;

	template <unsigned int CONSTNUM>
    class CalConstBuffer : public CalBuffer
    {
    public:

        CalConstBuffer(CalDevice* device);

        ~CalConstBuffer(void);

		template <unsigned int INDEX>
        void setConstant(void* data, CALformat format);

        bool setDataToBuffer();
    private:
        //! \brief CAL creates a buffer of multiple constants. 
        // _data points to the corresponding CPU array.
        float4 _data[CONSTNUM];
    };
}

#include "CALConstBufferDef.h"

#endif