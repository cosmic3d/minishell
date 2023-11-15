#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	printf("CWD = %s\n", getcwd(NULL, 0));

	chdir("/Users/apresas-");

	printf("CWD = %s\n", getcwd(NULL, 0));
	return (0);
}
