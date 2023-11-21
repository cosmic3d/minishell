/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_coso.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:48:28 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/21 17:56:22 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Este es el archivo donde hago temas de PATH, el nombre es provisional. De 
hecho, todo es provisional. */

/* Idea:

Antes de hacer fork, es necesario hacer varias cosas, entre ellas:

-Buscar si es necesario, el comando en el PATH
-Comprobar errores de lectura (falta de permisos)
-Comprobar si estamos intentando ejecutar un directorio
etc.

Todos estos checks tienen que ocurrir antes de intentar ejecutar el comando con
execve.

En caso de que todo este preámbulo vaya bien, el exit_status se mantendrá a 0
Pero si algo no funciona como esperabamos, entonces es necesario printear el 
error apropiado y setear el valor del exit_status para el valor de $?

Qué necesitamos:

- Una función de printeo de error formateada como:
minishell: <comando>: <mensaje de error>

- Una función que busque en los directorios del PATH el comando recibido
	Además debe tener en cuenta que If !PATH (PATH no existe o PATH="" o PATH existe pero no tiene content)
	Then el comando recibido será tratado como un file/directory. Estoy afecta el mensaje de error pero no el exit_status.

-  Una función que busque el comando en el directorio local (esto va siempre después de checkear el PATH)


*/


/* Opcionalmente esto puede no tener return y podemos hacer un return statement 
fuera de esta función tipo:
	return (execution_error(cmd, error), ms->exit_status);
Haciendo que esa función retorne el valor de exit_status, es solo una idea. */

/* Qué necesitamos?

- minishell en algún punto en el executor necesitará comprobar si el contenido 
de un token en particular corresponde con algún archivo en algún directorio 
que forme parte del $PATH

- Quizá necesitamos una función que retorne la dirección absoluta de un programa
si lo encontramos en el PATH

*/

/* Según lo que he entendido hasta ahora, el ejecutor segurá esta lógica:

1. Si el token a ejecutar contiene uno o más '/', entonces significa que el
token es un path/to/program y bash directamente buscará si ese programa existe
	1.1 Si existe, lo ejecuta.
	1.2 Si no existe, da error
		bash: <token>: No such file or directory
		$? = 127

2. Si el token a ejecutar NO contiene '/', entonces lo tratará como el nombre 
de un programa. Y hará lo siguiente:
	2.1 Busca un archivo con este nombre en los directorios estipulados por PATH
	en orden de aparición y, si lo encuentra en alguno de ellos, lo ejecuta.
	2.2 Si no lo encuentra en un directorio estipulado por PATH, entonces lo
	busca en el directorio actual y, si lo encuentra, lo ejecuta.
	2.3 Si no ha encontrado ningún archivo con ese nombre en ninguno de estos
	sitios, muestra este error:
		bash: <token>: No such file or directory
		$? = 127

2B. Si en algún momento encuentra el archivo pero este no tiene permisos de 
ejecución, parece ser que bash muestra este error:
		bash: <token>: Permission denied
Y da a $? el valor 126

Casos por definir:
	Si hago PATH="hola"
	y hago "ls" (en un directorio donde no exista un archivo llamado ls)
		bash: ls: command not found
		$? = 127
	Pero si hago unset PATH
	y hago "ls"
		bash: ls: No such file or directory
		$? = 127
	Lo mismo si hago PATH="" o PATH=

	Parece ser que si PATH no existe o está vacío, el error es "command not found"
	Pero si PATH existe, entonces es "No such file or directory"
	Ambos $? = 127


*/



// int	no_cmd_case(t_ms *ms)
// {
// 	if (path_exists(ms->env))
// 		return (ERR_CMD_NOT_FOUND); // 127 A
// 	else
// 		return (ERR_NO_SUCH_FILE); // 127 B
// }

// int	directory_check(char *cmd)
// {
// 	struct stat	statinfo;
// 	int			i;

// 	lstat(cmd, &statinfo);
// 	if (!S_ISREG(statinfo.st_mode))
// 	{
// 		i = 0;
// 		while (cmd[i])
// 		{
// 			if (cmd[i] == '/')
// 			{
// 				if (access(cmd, F_OK) == SUCCESS)
// 					return (ERR_IS_DIR);
// 				return (ERR_NO_SUCH_FILE);
// 			}
// 			i++;
// 		}
// 	}
// 	else if (S_ISDIR(statinfo.st_mode))
// 		return (ERR_CMD_NOT_FOUND);
// 	return (SUCCESS);
// }



// # define NOPATH 1
// # define YESPATH 0

// char	*find_in_path(char *name, t_ms *ms, int *flag)
// {
// 	char	*program;
// 	char	**path;
// 	int		i;

// 	path = get_path(ms->env, flag);
// 	i = 0;
// 	while (path[i])
// 	{
// 		program = get_file_in_directory(name, path[i]);
// 		if (program)
// 			break ;
// 		i++;
// 	}
// 	free(path);
// 	return (program);
// }

// char	**get_path(t_env *env, int *flag)
// {
// 	t_env	*path_env;
// 	char	**path_split;

// 	path_env = env_find("PATH", env);
// 	if (!path_env)
// 		return (NULL);
// 	if (!path_env->content[0]) // creo que este es el único check necesario
// 		return (NULL);
// 	*flag = YESPATH;
// 	path_split = ft_split(path_env->content, ':');
// 	if (!path_split)
// 		ms_quit(MALLOC_ERR);
// 	// aquí haré algunas pruebas por si acaso, printear el contenido y eso, pero en teoría está bien
// 	return (path_split);
// }

// char	*get_file_in_directory(char *filename, char *dir_path)
// {
// 	char	*filepath;

// 	filepath = ft_strjoin(dir_path, filename);
// 	if (!filepath)
// 		ms_quit(MALLOC_ERR);
// 	if (access(filepath, F_OK) != -1)
// 		return (filepath);
// 	else
// 	{
// 		free(filepath);
// 		return (NULL);
// 	}
// }
// char	*find_program(char *name, t_ms *ms)
// {
// 	char	*program;
// 	int		path_flag;

// 	path_flag = NOPATH;
// 	if (ft_strchr(name, '/')) // Si hay un '/'
// 		return (name); // Entonces name es un path/to/name
// 	program = find_in_path(name, ms, &path_flag);

// }

// /* NOTAS SOBRE PERMSSIONS:

// Tests:

// Ejecutando archivos dentro de directorios con permisos determinados:

// rwx 7 (111) -> OK
// rw- 6 (110) -> KO !
// r-x 5 (101) -> OK
// r-- 4 (100) -> KO !
// -wx 3 (011) -> OK
// -w- 2 (010) -> KO !
// --x 1 (001) -> OK

// Parece ser que lo único que necesito son permisos de ejecución. (LO MISMO CON CD <DIR>)

// Lo mismo parece ocurrir si se trata de un directorio dentro de otro, si todos ellos tienen permissos -x,
// se podrá ejecutar el programa si tienes el path exacto al archivo.

// */