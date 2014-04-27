
#include "stdio.h"

#define CommonHeader int i; double b; char* str

struct SomeNode {
	CommonHeader;
};


int main(void)
{
    char line[100];
	double a = 22222222222222222222222222222222222222222233333333.33333333343434343434343;
	
    printf("Test 1:%lf\n", a);
    fgets(line, 100, stdin); 
    printf("Test 1 line: %s\n", line);
    return 0;
}
