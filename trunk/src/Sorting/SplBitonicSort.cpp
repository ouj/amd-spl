#include "SplBitonicSort.h"
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
    namespace sorting
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

        bool BitonicSort::initModule(void)
        {
            return preInitCalProgram<SORT_ILPARA_LIST, BITONIC_SORT_IL>() && 
                preInitCalProgram<SORT_ILPARA_LIST, BITONIC_SORT_AT_IL>();
        }

        bool BitonicSort::bitonicSort(float *ptr, unsigned int _size)
        {
            CalDevice* device = CalRuntime::getInstance()->getDevice();
            CALdeviceinfo info = device->getInfo();
            if (_size <= info.maxResource1DWidth)
            {
                return BitonicSortImpl::bitonicSortImpl(ptr, _size);
            }
            else
            {
                return BitonicSortImpl::bitioncSortATImpl(ptr, _size);
            }
        }
    }
}