#include <iostream>
#include "Sort.h"

using namespace std;

int main(int argc, char* argv[])
{
    unsigned int tsize = 64; 

    char *p = new char[tsize];
    amdspl::Sort::BitonicSort(p, tsize);

    delete [] p;
	return 0;
}

