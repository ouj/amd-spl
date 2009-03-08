#include <iostream>
#include <vector>
#include "amdspl.h"
#include "BitonicSort.h"
#include <cassert>

using namespace std;

int main(int argc, char* argv[])
{
    BitonicSort bs(argv[0]);
    int retVal = 0;

    if (argc <= 1)
    {
        bs.Usage(argv[0]);
        exit(0);
    }

    amdspl::core::cal::DeviceManager *devMgr = 
        amdspl::core::cal::Runtime::getInstance()->getDeviceManager();
    assert(devMgr);
    if (!devMgr)
    {
        return -1;
    }
    else
    {
        bool res = devMgr->assignDevice(0);
        if (!res)
        {
            return -1;
        }
    }

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

