#include "BitonicSort.h"
#include <ctime>
#include <algorithm>
#include "amdspl.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief  Constructor
//! 
////////////////////////////////////////////////////////////////////////////////

BitonicSort::BitonicSort(char* name) : SampleBase(name)
{
    _lgArraySize = 0;
    _stage = 0;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief  Allocates memory for buffers used by application
//! 
////////////////////////////////////////////////////////////////////////////////

void
BitonicSort::allocateBuffer()
{
    unsigned int Width = info->Width;
    unsigned int Height = info->Height;
    unsigned int Length = Width * Height;

    _array1.resize(Length, 0);
    _array2.resize(Length, 0);
    _array3.resize(Length, 0);
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief  Fill the input bufers with random values
//! 
////////////////////////////////////////////////////////////////////////////////

void
BitonicSort::fillInputBuffer()
{
    unsigned int Width = info->Width;
    unsigned int Height = info->Height;
    unsigned int Length = Width * Height;
    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < Length; i++)
    {
        _array1[i] = (float)rand();
    }

    copy(_array1.begin(), _array1.end(), _array2.begin());
    copy(_array1.begin(), _array1.end(), _array3.begin());

    for (_stage = Length >> 1; _stage; _lgArraySize++)
    {
        _stage >>= 1;
    }
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief  Print timing information
//! 
////////////////////////////////////////////////////////////////////////////////

void
BitonicSort::printTimeInfo()
{
    int Width = info->Width;
    int Height = info->Height;

    double time = timer->GetElapsedTime();
	
    std::cout << std::setw(8) << "Width" << std::setw(8) << "Height"
                  << std::setw(16) << "Iterations" << std::setw(16) << "GPU Total Time" 
                  << std::endl;

    std::cout << std::setw(8) << info->Width << std::setw(8) << info->Height
                  << std::setw(16) << info->Iterations << std::setw(16) << time
                  << std::endl;

    std::cout << std::endl << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief  Verify against CPU implementation if requested 
//! 
////////////////////////////////////////////////////////////////////////////////

void
BitonicSort::verifyResults()
{
    unsigned int Width = info->Width;
    unsigned int Height = info->Height;
    unsigned int Length = Width * Height;
    int res = 0;

    std::cout<<"-e Verify correct output.\n";
    std::cout<<"Performing Bitonic Sort on CPU ... ";

    sort(_array2.begin(), _array2.end());
    
    std::cout << "Done\n";

    //res += Util::compareBuffers<float>(_array[0], _array[1], Height * Width);
    if (res)
    {
        std::cout << _name << ": Failed!\n\n";
    }
    else
    {
        std::cout << _name << ": Passed!\n\n" ;
    }
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief  Compare performance with CPU if requested
//! 
////////////////////////////////////////////////////////////////////////////////
void
BitonicSort::comparePerformance()
{
    unsigned int Width = info->Width;
    unsigned int Height = info->Height;
    unsigned int Length = Width * Height;
    unsigned int i;
	double cpuTime = 0.0;
	double gpuTime = 0.0;
    
    gpuTime = timer->GetElapsedTime();
    timer->Reset();
    timer->Start();
    
    std::cout << "-p Compare performance with CPU.\n";
	
    // Record CPU Total time
    //for(i = 0; i < info->Iterations; i ++)
    //{
        sort(_array2.begin(), _array2.end());
    //}
	
    timer->Stop();
    cpuTime = timer->GetElapsedTime() * info->Iterations;

	// Print CPU timing and speedup
	std::cout << std::setw(8) << "Width" << std::setw(8) << "Height"
              << std::setw(16) << "Iterations" << std::setw(16) << "CPU Total Time"
              << std::setw(16) << "GPU Total Time"
              << std::setw(16) << "Speedup" << std::endl;

    std::cout << std::setw(8) << info->Width << std::setw(8) << info->Height
              << std::setw(16) << info->Iterations << std::setw(16) << cpuTime
              << std::setw(16) << gpuTime
              << std::setw(16) << cpuTime / gpuTime << std::endl;
	
    std::cout << std::endl << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief  backend implementation for the sample
//! 
////////////////////////////////////////////////////////////////////////////////

int
BitonicSort::run()
{
    unsigned int retVal = 0;
    unsigned int Width = info->Width;
    unsigned int Height = info->Height;
    unsigned int Length = Width * Height;
    
    {
        unsigned int dim1D[] = {Length};
        unsigned int flip = 0;
        unsigned int i;

		amdspl::ILPROGRAMS_INDEX progIdxs[] = {
			amdspl::BITONIC_SORT_IL, 
			amdspl::BITONIC_SORT_AT_IL, 
			amdspl::ILPRGROGRAMS_NUM
		};
		
		::amdspl::preInitSPL(progIdxs);

        timer->Start();
        // Record CPU Total time
        for(i = 0; i < info->Iterations; i ++)
        {
            ::amdspl::SPLSort::bitonicSort(&_array1[0], _array1.size());
        }


        timer->Stop();
    }

    return retVal;
}

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief  Destructor
//! 
////////////////////////////////////////////////////////////////////////////////

BitonicSort ::~BitonicSort()
{
}
