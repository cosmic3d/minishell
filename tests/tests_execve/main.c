#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	char	*argv[] = { "bash", NULL };
	char	*envp_1[] = { "HOME=/Users/apresas-", NULL };
	// envp_1 solo contiene HOME
	char	*envp_2[] = { NULL };
	// envp_2 solo contiene NULL, es decir: envp existe pero !envp[0]
	char	*envp_3[] = { "", NULL};
	// envp existe, envp[0] existe, envp[0][0] no existe
	char	*envp_4[] = { "1WRONG=este argumento tiene un nombre incorrecto", NULL};
	// envp[1] esta mal, y ya
	char	*envp_5[] = { "RIGHT=este argumento esta bien", "1WRONG=este no", "RIGHT2=vuelve a estar bien", NULL};
	// envp[1] bien, [2] mal, [3] bien
	char	*envp_6[] = { "123", "hola que tal", "^13'6=hola", NULL};
	char	*envp_7[] = { "=123", "''=hola que tal", "===^13'6=hola", "==hola", "-=hola", "'=", "'=holi", ";=wenas", "=e=hola", NULL};

	char	*envp_A1[] = { "SHLVL=1", "PWD=here", "OLDPWD=misco", "1WRONG=que pasa", "2WRONG=", "!#%1;\'?/,=hola", NULL};

	"nombre=content", "nombre", "1hola=hola"

	// execve("/bin/bash", argv, envp_1);
	// execve("/bin/bash", argv, envp_2);
	// execve("/bin/bash", argv, envp_3);
	// execve("/bin/bash", argv, envp_4);
	// execve("/bin/bash", argv, envp_5);
	// execve("/bin/bash", argv, envp_6);
	// execve("/bin/bash", argv, envp_7);
	execve("../minishell_aux/minishell", argv, envp_A1);
	return (0);
}