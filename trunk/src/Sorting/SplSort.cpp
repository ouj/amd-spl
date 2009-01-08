#include "SplSort.h"
#include "SplBitonicSortImpl.h"
#include "cal.h"
#include "calcl.h"
#include "CALDevice.h"
#include "CALRuntime.h"
#include "Sort_IL.h"
#include "CALProgram.h"
#include <cassert>

namespace amdspl
{
    template<typename ILPARA_LIST, unsigned int ID>
    bool preInitCalProgram(void)
    {
        CalProgram<ILParaByID<ILPARA_LIST, ID>::Result>* program = 
            CalProgram<ILParaByID<ILPARA_LIST, ID>::Result>::getInstance();

        assert(program); 
        if (!program) 
            return false;

        return true;
    };

    bool SPLSort::initModule(void)
    {
        return preInitCalProgram<SORT_ILPARA_LIST, BITONIC_SORT_IL>() && 
            preInitCalProgram<SORT_ILPARA_LIST, BITONIC_SORT_AT_IL>();
    }

    bool SPLSort::bitonicSort(float *ptr, unsigned int _size)
    {
		CalDevice* device = CalRuntime::getInstance()->getDevice();
		CALdeviceinfo info = device->getInfo();
		if (_size <= info.maxResource1DWidth)
		{
            return SplBitonicSortImpl::bitonicSortImpl(ptr, _size);
		}
		else
		{
			return SplBitonicSortImpl::bitioncSortATImpl(ptr, _size);
		}
    }
}