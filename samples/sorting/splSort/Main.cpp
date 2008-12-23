#include <iostream>
#include <vector>
#include "BitonicSort.h"

using namespace std;

int main(int argc, char* argv[])
{
    BitonicSort bs(argv[0]);
    int retVal = 0;

    // Parse command line options
    bs.ParseCommandLine(argc, argv);

    // Allocate buffers
    bs.allocateBuffer();

    // Fill the input buffers with random values
    bs.fillInputBuffer();

    // Run GPU kernel
    retVal = bs.run();

    // Display timing informations
    if(bs.info->Timing)
    {
        bs.printTimeInfo();
    }

    // Verify result with CPU
    if(bs.info->Verify)
    {
        bs.verifyResults();
    }

    // Compare performance with CPU
    if(bs.info->Performance)
    {
        bs.comparePerformance();
    }

    return retVal;
}

