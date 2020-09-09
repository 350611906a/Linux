#include <unistd.h>
#include <stdio.h>
extern char** environ;

int main(void)
{
    printf("This is hello process pid=%d\n", getpid());
    
    return 0;
}

