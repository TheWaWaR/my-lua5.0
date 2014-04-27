
#include "stdio.h"

#define cast(t, v)	((t)(v))

int main(void)
{
    {int a=3; a++; --a;}
    printf("This is Test 2.<(char unsigned)(~0): %d>\n", cast(char unsigned, ~0));
    return 0;
}
