
/* example1: hook global function */

#include <stdio.h>
#include "cpphook.h"


extern"C" int function(int i1, int i2, int i3, double d1, double d2)
{
    printf("call function. i1=%d, i2=%d, i3=%d, d1=%f, d2=%f\n", i1, i2, i3, d1, d2);
    return 1;
}

int function__hook(int i1, int i2, int i3, double d1, double d2)
{
    printf("call function__hook. i1=%d, i2=%d, i3=%d, d1=%f, d2=%f\n", i1, i2, i3, d1, d2);
    return 2;
}

int main()
{
    int r;

    r = function(1,2,3,4.0,5.0);
    printf("function return: %d\n", r);
    
    install_hook("function", (void*)function__hook);
    
    r = function(1,2,3,4.0,5.0);
    printf("function return: %d\n", r);

    return 0;
}