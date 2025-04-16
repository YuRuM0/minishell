#include <unistd.h>
# include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd;
	fd = open("script_test", O_RDWR);
	printf("%d\n", fd);
	close(fd);
	perror("first");
	close(fd);
	perror("first");
	printf("%d\n", fd);
	return (0);
}