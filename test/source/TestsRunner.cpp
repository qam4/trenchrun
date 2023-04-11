/*
 * File:   TestsRunner.cpp
 *
 */

#include <cstdlib>
#include <ctime>

#include "Tests.h"

/*
 *
 */
int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    Tests::run();

    return 0;
}
