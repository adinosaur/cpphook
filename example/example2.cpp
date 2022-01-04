
/* example2: hook class static function and method */

#include <stdio.h>
#include "cpphook.h"

struct MyStruct
{
    static int function(int i1, int i2, int i3, double d1, double d2)
    {
        printf("call MyStruct::function. i1=%d, i2=%d, i3=%d, d1=%f, d2=%f\n", i1, i2, i3, d1, d2);
        return 1;
    }

    int method(int i1, int i2, int i3, double d1, double d2)
    {
        printf("call MyStruct::method. i1=%d, i2=%d, i3=%d, d1=%f, d2=%f\n", i1, i2, i3, d1, d2);
        return 2;
    }
};

int MyStruct_function__hook(int i1, int i2, int i3, double d1, double d2)
{
    printf("call MyStruct_function__hook. i1=%d, i2=%d, i3=%d, d1=%f, d2=%f\n", i1, i2, i3, d1, d2);
    return 3;
}

int MyStruct_method__hook(struct MyStruct* self, int i1, int i2, int i3, double d1, double d2)
{
    printf("call MyStruct_method__hook. i1=%d, i2=%d, i3=%d, d1=%f, d2=%f\n", i1, i2, i3, d1, d2);
    return 4;
}

int main()
{
    int r;

    MyStruct inst;

    r = inst.function(1,2,3,4.0,5.0);
    printf("inst.function return: %d\n", r);

    r = inst.method(1,2,3,4.0,5.0);
    printf("inst.method return: %d\n", r);
    
    install_hook("_ZN8MyStruct8functionEiiidd", (void*)MyStruct_function__hook);
    install_hook("_ZN8MyStruct6methodEiiidd", (void*)MyStruct_method__hook);
    
    r = inst.function(1,2,3,4.0,5.0);
    printf("inst.function return: %d\n", r);

    r = inst.method(1,2,3,4.0,5.0);
    printf("inst.method return: %d\n", r);

    return 0;
}