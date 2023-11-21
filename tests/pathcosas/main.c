#include <unistd.h>

int	main(void)
{
	char str[6] = "Hola\n\0";

	write(1, &str, 5);
	return (0);
}

