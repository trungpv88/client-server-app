#include <stdio.h>
#include <stdlib.h>
#include "include/server.h"
#include "include/execute.h" // to call Concat function

void InitializeParameters(char *argv[])
{
    char* dir = "\\";
    PORT = atoi(argv[1]);
    SOURCE_DIRECTORY = Concat(argv[2], dir);
    INPUT_DIR = Concat(argv[3], dir);
    OUTPUT_DIR = Concat(argv[4], dir);
    CHECK_POINT_DIR = Concat(argv[5], dir);
    TIME_EXECUTION_LIMIT = atoi(argv[6]);
}

int main(int argc, char *argv[])
{
    InitializeParameters(argv);
    StartSession();
    return 0;
}
