#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	write(1, "Hola\n", 5);
	return (0);
}
