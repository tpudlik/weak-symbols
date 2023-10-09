
#include "stdio.h"
#include "weak.h"

void Caller()
{
    printf("Calling Callback: \n");
    Callback();
}

__attribute__((weak)) void Callback() { printf("weak Callback!\n"); }
