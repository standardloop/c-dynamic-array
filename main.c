#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./dynamic-array.h"

int main(void)
{
    DynamicArray *dynamicArray = DefaultDynamicArrayInit();
    if (dynamicArray == NULL)
    {
        return EXIT_FAILURE;
    }
    char *test = malloc(sizeof(char) * 6);
    strcpy(test, "hello");

    DynamicArrayAdd(dynamicArray, test);

    int *foo = malloc(sizeof(int) * 6);
    foo[0] = 1;
    foo[1] = 2;
    foo[2] = 3;
    foo[3] = 4;
    foo[4] = 5;
    foo[5] = 6;
    DynamicArrayAdd(dynamicArray, foo);

    PrintDynamicArray(dynamicArray);

    FreeDynamicArray(dynamicArray);
    return EXIT_SUCCESS;
}
