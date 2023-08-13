#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    int a = 33;
    float b = 12.13;
    char c = 'K';
    char str[] = "Komal";
    printf("a = %d, b = %f, c = %c, str = %s, Hexadecimal for a = %x\n", a, b, c, str, a);
    errno = EPERM;
    printf("Error Access Number : %m\n");
    return 0;
}
