#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*argv[] = { "arg0", NULL};

	char	*aNull[] = { NULL };
	char	*aErr[] = { "Invalid argument", "VALID=holi" };
	char	*aBad1[] = { "Invalid argument", NULL};
	char	*aMin1[] = { "SHLVL=1", "OLDPWD=Buenas", "PWD=/here/it/is", NULL};
	char	*aShlvlNeg1[] = { "SHLVL=-9135342", NULL };
	char	*aShlvlNeg2[] = { "SHLVL=-0", NULL };
	char	*aShlvlNeg3[] = { "SHLVL=--0", NULL };
	char	*aShlvlNeg4[] = { "SHLVL=-1", NULL };
	char	*aShlvlNeg5[] = { "SHLVL=-8", NULL };
	char	*aShlvlNeg6[] = { "SHLVL=-2147482647", NULL };
	char	*aShlvlNeg7[] = { "SHLVL=-2147482647", NULL };
	char	*aShlvlNeg8[] = { "SHLVL=-2147482647", NULL };
	char	*aShlvlNeg9[] = { "SHLVL=-", NULL };
	char	*aShlvl1[] = { "SHLVL=1", NULL };
	char	*aShlvl2[] = { "SHLVL=15", NULL };
	char	*aShlvl3[] = { "SHLVL=123456789", NULL };
	char	*aShlvl4[] = { "SHLVL=2147483646", NULL };
	char	*aShlvl5[] = { "SHLVL=2147483647", NULL };
	char	*aShlvl6[] = { "SHLVL=2147483648", NULL };
	char	*aShlvl7[] = { "SHLVL=2147483649", NULL };
	char	*aShlvl8[] = { "SHLVL=998", NULL };
	char	*aShlvl9[] = { "SHLVL=999", NULL };
	char	*aShlvl10[] = { "SHLVL=1000", NULL };
	char	*aShlvl11[] = { "SHLVL=1001", NULL };
	char	*aShlvl12[] = { "SHLVL=8888888888888888888", NULL };
	char	*aShlvl13[] = { "SHLVL=", NULL };
	char	*aShlvl14[] = { "SHLVL", NULL };
	char	*aShlvl15[] = { "SHLVl=123", NULL };
	char	*aShlvl16[] = { "SHLVL=+13593", NULL };
	char	*aShlvl17[] = { "SHLVL=+248", NULL };
	char	*aShlvl18[] = { "SHLVL=+0", NULL };
	char	*aShlvl19[] = { "SHLVL=0", NULL };
	char	*aShlvl20[] = { "SHLVL=invalid", NULL };
	char	*aShlvl21[] = { "SHLVL=123invalid", NULL };
	char	*aShlvl23[] = { "SHLVL=18446744073709551616", NULL };
	char	*aShlvl24[] = { "SHLVL=9223372036854775808", NULL };
	char	*aShlvl25[] = { "SHLVL=4292496729524224224", NULL };
	char	*aShlvl26[] = { "SHLVL=4611686018427387904", NULL };
	char	*aShlvl27[] = { "SHLVL=4611686016279904255", NULL }; // limite warning shlvl too high
	char	*aShlvl28[] = { "SHLVL=4611686018427387904", NULL };
	char	*aShlvl29[] = { "SHLVL=17446744069523551616", NULL };
	char	*aShlvl22[] = { "SHLVL=6442450943", NULL };


	// execve("/home/albert/minishell/minishell", argv, aNull);
	// execve("/bin/bash", argv, aNull);
	// execve("/home/albert/minishell/minishell", argv, aErr);
	// execve("/bin/bash", argv, aErr);
	// execve("/home/albert/minishell/minishell", argv, aBad1);
	// execve("/bin/bash", argv, aBad1);
	// execve("/home/albert/minishell/minishell", argv, aMin1);
	// execve("/bin/bash", argv, aMin1);
	// execve("/home/albert/minishell/minishell", argv, aShlvlNeg1);
	// execve("/bin/bash", argv, aShlvlNeg1);
	// execve("/home/albert/minishell/minishell", argv, aShlvlNeg2);
	// execve("/bin/bash", argv, aShlvlNeg2);
	// execve("/home/albert/minishell/minishell", argv, aShlvlNeg3);
	// execve("/bin/bash", argv, aShlvlNeg3);
	// execve("/home/albert/minishell/minishell", argv, aShlvlNeg4);
	// execve("/bin/bash", argv, aShlvlNeg4);
	// execve("/home/albert/minishell/minishell", argv, aShlvlNeg5);
	// execve("/bin/bash", argv, aShlvlNeg5);
	// execve("/home/albert/minishell/minishell", argv, aShlvlNeg6);
	// execve("/bin/bash", argv, aShlvlNeg6);
	// execve("/home/albert/minishell/minishell", argv, aShlvlNeg7);
	// execve("/bin/bash", argv, aShlvlNeg7);
	// execve("/home/albert/minishell/minishell", argv, aShlvlNeg8);
	// execve("/bin/bash", argv, aShlvlNeg8);
	// execve("/home/albert/minishell/minishell", argv, aShlvlNeg9);
	// execve("/bin/bash", argv, aShlvlNeg9);
	// execve("/home/albert/minishell/minishell", argv, aShlvl1);
	// execve("/bin/bash", argv, aShlvl1);
	// execve("/home/albert/minishell/minishell", argv, aShlvl2);
	// execve("/bin/bash", argv, aShlvl2);
	// execve("/home/albert/minishell/minishell", argv, aShlvl3);
	// execve("/bin/bash", argv, aShlvl3);
	// execve("/home/albert/minishell/minishell", argv, aShlvl4);
	// execve("/bin/bash", argv, aShlvl4);
	// execve("/home/albert/minishell/minishell", argv, aShlvl5);
	// execve("/bin/bash", argv, aShlvl5);
	// execve("/home/albert/minishell/minishell", argv, aShlvl6);
	// execve("/bin/bash", argv, aShlvl6);
	// execve("/home/albert/minishell/minishell", argv, aShlvl7);
	// execve("/bin/bash", argv, aShlvl7);
	// execve("/home/albert/minishell/minishell", argv, aShlvl8);
	// execve("/bin/bash", argv, aShlvl8);
	// execve("/home/albert/minishell/minishell", argv, aShlvl9);
	// execve("/bin/bash", argv, aShlvl9);
	// execve("/home/albert/minishell/minishell", argv, aShlvl10);
	// execve("/bin/bash", argv, aShlvl10);
	// execve("/home/albert/minishell/minishell", argv, aShlvl11);
	// execve("/bin/bash", argv, aShlvl11);
	// execve("/home/albert/minishell/minishell", argv, aShlvl12);
	// execve("/bin/bash", argv, aShlvl12);
	// execve("/home/albert/minishell/minishell", argv, aShlvl13);
	// execve("/bin/bash", argv, aShlvl13);
	// execve("/home/albert/minishell/minishell", argv, aShlvl22);
	execve("/bin/bash", argv, aShlvl22);

	return (0);
}

/*

aNULL: [GOOD]

MINISHELL:

./tester
minishell 🐌🐚 env
SHLVL=1
PWD=/home/albert/minishell
minishell 🐌🐚 export
declare -x OLDPWD
declare -x PWD="/home/albert/minishell"
declare -x SHLVL="1"
minishell 🐌🐚 

BASH:

./tester
minishell$ env
PWD=/home/albert/minishell
SHLVL=1
_=/usr/bin/env
minishell$ export
declare -x OLDPWD
declare -x PWD="/home/albert/minishell"
declare -x SHLVL="1"

--------------------
About aErr1:

aErr1 tiene un contenido que no acaba en NULL
A bash le da igual, esto puede dar errores de diversos tipos probablemente, pero
por lo que parece, bash no se queja de nada. Tampoco es que bash pueda saber
que envp no termina en NULL, simplemente sigue. Y nosotros igual, no podemos saberlo.
Así que todo bien en este sentido.

--------------------

aBad1:

MINISHELL:
./tester
minishell 🐌🐚 env
SHLVL=1
PWD=/home/albert/minishell
minishell 🐌🐚 export
declare -x OLDPWD
declare -x PWD="/home/albert/minishell"
declare -x SHLVL="1"

BASH:
./tester
minishell$ env
PWD=/home/albert/minishell
SHLVL=1
_=/usr/bin/env
minishell$ export
declare -x OLDPWD
declare -x PWD="/home/albert/minishell"
declare -x SHLVL="1"

aMin1:

MINISHELL:
./tester
minishell 🐌🐚 env
SHLVL=2
PWD=/home/albert/minishell
minishell 🐌🐚 export
declare -x OLDPWD
declare -x PWD="/home/albert/minishell"
declare -x SHLVL="2"

BASH:
./tester
minishell$ env
PWD=/home/albert/minishell
SHLVL=2
_=/usr/bin/env
minishell$ export
declare -x PWD="/home/albert/minishell"
declare -x SHLVL="2"

// ???? Aqui bash no inicializa OLDPWD, pero esto hay que testearlo en los mac
de 42 por que allí estoy convencido de que sí inicializa OLDPWD sin falta.

NOTA INTERESANTE:

Al parecer, bash obtiene su nombre dentro de si mismo en base al argumento que
le llama. Si lo llamas mediante el comando "bash", el argumento 0 de bash
será bash, y por lo tanto los mensajes de error dirán:
bash: error noseque: nosecuantos

Pero si usamos execve, podemos hacer que el argv que lo llama diga lo que
queramos, si hacemos que argv[0] diga "misco", entonces bash printeará los 
mensajes de error en base a ese nombre, por ejemplo:
misco: error noseque: nosecuantos

Podemos fácilmente imitar esto en nuestro minishell si queremos.

NOTA SOBRE SHLVL MUY MUY ALTOS:

Sospecho que la forma en que bash resuelve estos conflictos en debian es
distinta a la forma en que los resuelve en los macs de 42.

Habrá que probar en el campus casos extremos. Como mínimo puedo decir esto:

En debian, si enviamos un valor tan alto que haga overflow y de la vuelta
a un int, simplemente se seguirá el bucle. Es decir,
si recibo un SHLVL de 2147483648, que INT_MAX + 1, es lo mismo que decir
INT_MIN. Y por lo tanto, bash entiende que ha recibido un SHLVL negativo.
Por lo tanto, lo setea a 0.

Pero en los macs de 42, ocurren otras cosas. Parece que trabajen con
longs a veces. Es más confuso.

Si veo que en 42 es muy lioso, lo que haré será usar un sistema
más simple pero funcional como el de bash en debian.

Por ahora lo dejo como está.

Pero el sistema de bash en debian me parece mucho más simple y elegante.

Coge el valor de SHLVL y conviertelo a digitos.
Si hay caracters inválidos, no puedes convertirlo, entonces SHLVL=1 y ya
Si todo son caracteres válidos, recoge el numero y castealo a un int y
que sea lo que tenga que ser. Va a loopear una y otra vez.

El limite ocurre, creo en los margenes de un long. A verlo.

Lógica que he sacado de lo que hace bash:

Get (old)SHLVL into long
If shlvl_long < 0
	SHLVL=1
Elif shlvl_long >= 0
	cast (int)shlvl_long into shlvl_int
	If shlvl_int > 1000
		Print warning && SHLVL=1
		Unless shlvl_long > 2^62 (or +1, -1, >=, no sé exactamente)
			Then don't print warning
	If shlvl_int < 0
		SHLVL=0

*/