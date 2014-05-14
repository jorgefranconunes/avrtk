/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/CommandLineTestRunner.h>





int main(int argc, char** argv) {

    int result = CommandLineTestRunner::RunAllTests(argc, argv);

    return result;
}

