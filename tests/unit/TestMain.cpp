// TestMain.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "gtest/gtest.h"


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS();
}

