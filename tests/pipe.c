#include <unistd.h>
# include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd;
	// int pid;
	char *a[2] = {"eduarda", "filipe"};

	// pid = open("../out", O_RDWR);
	fd = fork();
	if (fd == 0)
	{
		a[1] = NULL;
		printf("%s\n", a[0]);
		printf("%s\n", a[1]);
		// printf("%s\n", a);
		exit(0);
	}
	wait(NULL);
	printf("%s\n", a[0]);
	printf("%s\n", a[1]);
	return (0);
}