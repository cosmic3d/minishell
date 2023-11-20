#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int value = access(argv[1], F_OK);
	
	if (errno != 0)
	{
		perror("error");
		// return (0);
	}

	printf("access = %d\n", value);
	return (0);
}
