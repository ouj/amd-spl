// TestMain.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include "tchar.h"
#include "gtest\gtest.h"


int _tmain(int argc, _TCHAR* argv[])
{
    testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS();
	return 0;
}
