
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *endptr;

    printf("%s\n", argv[1]);
    double res = strtod(argv[1], &endptr);
    printf("result:%lf, endstr(%d): %s\n", res, strlen(endptr), endptr);
    return 0;
}
