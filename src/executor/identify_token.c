/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:58:25 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/22 17:31:47 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prolly not
/* Aquí van a ir las funciones necesarias para identificar un token.
En este caso me refiero a convertir un token en una dirección de archivo.

Según qué token sea, se tendrá que seguir un procedimiento u otro.
Ejemplo:
ls -l > cat

Token 0: ls
Token 1: -l
token 2: >
token 3: cat

En este caso, t0 es un comando, para este tipo de token hay que buscar en el 
PATH o en el directorio actual, etc. Y convertirlo a la dirección de archivo 
correcta. Esta es la conversión:

ls => /bin/ls

El siguiente token, t1, es una flag. Las flags no sé si las trataré como tal o 
como un un argumento. Es decir, para ls, -l no es algo especial, simplemente es
el argv[1], por ello, creo que no es necesario tratar de forma especial las 
flags.

t1 es, por lo tanto, un argumento.
Los argumentos no han de ser convertidos.

-l => -l

El token t2 es una redirección. El tokenizer ya se encarga de identificar estos 
de forma especial así que no hay problema. No hay que expandir nada.

> => >

Y finalmente el token t3 es especificamente un archivo. Entiendo que los tokens 
que van después de una redirección [>, <, >>, <<] son archivos.
Hay que expandirlo pero solamente hay que buscar en el directorio actual, CREO.
En este caso, si existiese tal archivo, habría que expandirlo, a su dirección
relativa a donde se encuentre minishell (o quizá su dirección absoluta, si es
más fácil de hacer, aunque quizá no es correcto). Si no se encuentra el archivo,
entonces lo crea con (por lo que veo) estos permisos: -rw-r--r-- (chmod 644).
Si el archivo sí que existe, entonces se convierte este token a su dirección.
De todos modos, creo que la parte de crear el archivo está fuera del scope de 
esta parte del minishell y debería suceder más adelante.
Pero de todos modos ya que lo estoy mirando, voy a ver qué permisos son 
necesarios para que > funcione.

Para que > funcione, solo son necesarios los permisos de escritura.
Si el archivo no tiene permisos de escritura, el error es:
"Permission denied"
exit_status = 1

Si tenemos varias redirecciones, en el momento en el que el error sucede, se 
dejan de hacer comprobaciones. Aunque por lo menos en el caso de >, los archivos
que se den en la cadena de redirecciones antes que el archivo sin permisos se 
encuentre son creados igualmente.


Ejemplo:
	Asumamos que hay un archivo en el directorio actual llamado "bad" que no 
	tiene permisos de escritura.

echo hola > bad
	Esto resultará en el error Permission denied y exit_status = 1

echo hola > file1 > file2 > bad > file3
	Esto resultará en la creación de file1 y file2 (si no existen), luego se 
	dará el error Permission Denied exit_status = 1. file3 no llegará a ser 
	comprobado y no se creará.

Claramente, este error no puede ser gestionado por el expansor de filepaths 
por que el expansor de filepaths no se encarga de crear archivos en caso de que 
no existan, etc.

Duda, es necesario expandir los filepaths para los tokens de tipo ARCHIVO?
O podemos asumir que todos representan de forma natural una dirección relativa 
al cwd?
	Es decir, hace falta convertir "file" a "./file" ? O para lo que nos 
	interesa, "file" cumple la misma función que "./file"?
He hecho un poco de investigación y he llegado a la conclusión de que no hace 
falta expandir los archivos. "file" puede ser interpretado correctamente como la
dirección relativa al archivo de nombre "file".

Conclusión sobre la expansión de tokens:

Los únicos tokens que hay que expandir, son los "comandos". La forma en que 
podemos identificar un comando es:
El primer token que por descarte no es una redirección o un archivo.
Todo token que sea directamente siguiente a un pipe.
Ejemplos:

< infile cat

El primer token solo puede ser o una REDIRECCIÓN o un COMANDO.

En este caso el primer token es "<", una REDIRECCIÓN, por lo tanto, el siguiente
token, "infile", ha de ser por fuerza un ARCHIVO.
El siguiente token no es una REDIRECCIÓN, por lo tanto ha de ser un COMANDO.

> file echo "Hola que tal"

En este caso, el primer token es ">" una REDIRECCIÓN, por lo tanto, el siguiente
token, "file", ha de ser por fuerza un ARCHIVO.
El siguiente token no es una REDIRECCIÓN, por lo tanto ha de ser un COMANDO.

echo hola | cat file

Aunque este comando no entiendo que hace exactamente, la cuestión es la 
siguiente: El primer comando no es una REDIRECCIÓN, por lo tanto es un COMANDO.
Lo que sigue a un comando, no es una REDIRECCIÓN ni un PIPE, por lo tanto es un
ARGUMENTO. El siguiente token es un PIPE, por lo tanto, el que le sigue, "cat" 
ha de ser un COMANDO. Y el token que va después no es una REDIRECCIÓN ni un 
PIPE, por lo tanto es un ARGUMENTO.
*/
