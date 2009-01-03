#ifndef _AMDSPL_CALCONSTBUFFER_DEF_H_
#define _AMDSPL_CALCONSTBUFFER_DEF_H_

namespace amdspl
{
	template <unsigned int CONSTNUM>
	CalConstBuffer<CONSTNUM>::CalConstBuffer(CalDevice* device) : 
	CalBuffer(1, (unsigned int*)device, CAL_FORMAT_FLOAT_4, BUFFER_HOST, 0, device)
	{
		_dimensions = new unsigned int[1];
		_dimensions[0] = CONSTNUM;

		memset((void*)_data, 0, sizeof(float4) * CONSTNUM);
	}

	////////////////////////////////////////////////////////////////////////////////
	//!
	//! \brief Sets the cpu pointer data with constant values
	//!
	////////////////////////////////////////////////////////////////////////////////
	template <unsigned int CONSTNUM>
	template <unsigned int INDEX>
	void
		CalConstBuffer<CONSTNUM>::setConstant(void* data, CALformat format)
	{
		unsigned short bytes = amdspl::utils::getElementBytes(format);
		memcpy(&_data[INDEX], data, bytes);
	}

	template <unsigned int CONSTNUM>
	CalConstBuffer<CONSTNUM>::~CalConstBuffer()
	{
	}

	////////////////////////////////////////////////////////////////////////////////
	//!
	//! \brief Transfer data from cpu pointer _data to GPU buffer
	//!
	////////////////////////////////////////////////////////////////////////////////

	template <unsigned int CONSTNUM>
	bool
		CalConstBuffer<CONSTNUM>::setDataToBuffer()
	{
		CALuint pitch;
		void* data = getBufferPointerCPU(pitch);
		if(!data)
		{
			return false;
		}

		memcpy(data, _data, sizeof(float4) * CONSTNUM);
		freeBufferPointerCPU();

		return true;
	}
};

#endif