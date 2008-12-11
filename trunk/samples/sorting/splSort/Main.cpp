#include <iostream>
#include "splSort.h"

using namespace std;

int main(int argc, char* argv[])
{
    unsigned int tsize = 64; 

    int *p = new int[tsize];
    amdspl::SPLSort::bitonicSort(p, tsize);

    delete [] p;
	return 0;
}

