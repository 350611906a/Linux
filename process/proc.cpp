#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("Entering main ...\n");
	printf("This main pid : %d\n", getpid());
    int ret;
	int count = 0;
	//sint status = -1;
	while(count != -2)
	{
		ret = fork();
		if(ret == 0)
		{
			ret = execl("./hello", "hello", NULL);
			if(ret == -1)
			{
				perror("execl error");
				while(1)
				{
					printf("=========error\n");
				}
			}
		}
		else
		{
			printf("Entering main again ...\n");
			//wait(&status);
		}
		//sleep(1);
		count++;
	}	
    
    printf("Exiting main ...\n");
	
    return 0;
}
