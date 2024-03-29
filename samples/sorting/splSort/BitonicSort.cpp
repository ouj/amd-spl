#include "BitonicSort.h"
#include <ctime>
#include <algorithm>
#include "amdspl.h"
#include <float.h>
#include "assert.h"
#include <functional>

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
        _array1[i] = (float)rand() / INT_MAX;
    }

    copy(_array1.begin(), _array1.end(), _array2.begin());
    copy(_array1.begin(), _array1.end(), _array3.begin());
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

    sort(_array3.begin(), _array3.end(), greater<float>());
    
    std::cout << "Done\n";

    //res += Util::compareBuffers<float>(_array[0], _array[1], Height * Width);
    for (unsigned int i = 0; i < _array1.size(); i++)
    {
        if (_array1[i] != _array3[i])
        {
            res = 1;
            assert(false);
            std::cout <<  "Sorting Failed at " << i << ": CPU(" << setprecision(10) << _array3[i] 
            << "), GPU(" <<  setprecision(10) << _array1[i] << ")\n";
        }
    }

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
    std::cout << "-p Compare performance with CPU.\n";

    // Record CPU Total time
    for(i = 0; i < info->Iterations; i ++)
    {
        vector<float> tmpArray(_array2.begin(), _array2.end());
        timer->Start();
        sort(tmpArray.begin(), tmpArray.end());
        timer->Stop();
    }
    cpuTime = timer->GetElapsedTime();

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

        timer->Reset();
        // Record CPU Total time
        for(i = 0; i < info->Iterations; i ++)
        {
            timer->Start();
            ::amdspl::sorting::BitonicSort::sort(&_array1[0], 
                static_cast<unsigned int>(_array1.size()), false);
            timer->Stop();
        }
        
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
