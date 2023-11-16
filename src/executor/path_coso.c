/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_coso.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:48:28 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/16 18:21:59 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Este es el archivo donde hago temas de PATH, el nombre es provisional. De 
hecho, todo es provisional. */

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

# define NOPATH 1
# define YESPATH 0

char	*find_in_path(char *name, t_ms *ms, int *flag)
{
	char	*program;
	char	**path;
	int		i;

	path = get_path(ms->env, flag);
	i = 0;
	while (path[i])
	{
		program = get_file_in_directory(name, path[i]);
		if (program)
			break ;
		i++;
	}
	free(path);
	return (program);
}

char	**get_path(t_env *env, int *flag)
{
	t_env	*path_env;
	char	**path_split;

	path_env = env_find("PATH", env);
	if (!path_env)
		return (NULL);
	if (!path_env->content[0]) // creo que este es el único check necesario
		return (NULL);
	*flag = YESPATH;
	path_split = ft_split(path_env->content, ':');
	if (!path_split)
		ms_quit(MALLOC_ERR);
	// aquí haré algunas pruebas por si acaso, printear el contenido y eso, pero en teoría está bien
	return (path_split);
}

char	*get_file_in_directory(char *filename, char *dir_path)
{
	char	*filepath;

	filepath = ft_strjoin(dir_path, filename);
	if (!filepath)
		ms_quit(MALLOC_ERR);
	if (access(filepath, F_OK) != -1)
		return (filepath);
	else
	{
		free(filepath);
		return (NULL);
	}
}

char	*find_program(char *name, t_ms *ms)
{
	char	*program;
	int		path_flag;

	path_flag = NOPATH;
	if (ft_strchr(name, '/')) // Si hay un '/'
		return (name); // Entonces name es un path/to/name
	program = find_in_path(name, ms, &path_flag);

}