/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_filepath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:35:49 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/22 18:14:13 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TO-DO:

Arreglar los casos de PATH con rutas relativas.
Con las rutas relativas me parecía que bash printeaba los errores así:
bash: testpath/misco: No such file or directory
Pero resulta que eso solo es por que bash parece conservar un registro interno
de archivos a los que ha accedido recientemente.
Me explico mejor:
bash se acuerda de que anteriormente has abierto un archivo en un directorio
relativo indicado por PATH. Por lo tanto, al hacer:
"misco" (asumiendo que existe ese archivo en el directorio relativo)
(y asumiendo que ahora mismo no podemos acceder al directorio relativo en 
questión)
el error será:
bash: <directorio>/misco: No such file or directory
Pero si hicies cualquier otro comando, por ejemplo "jones", entonces
bash simplemente dirá:
bash: jones: command not found
Como nosotros no gestionamos esa clase de cosas, registros de en qué archivos
ya hemos accedido relativo a qué otros archivos bla bla bla...
Entonces podemos pasar de esto..

Quizá hay más por ver

Caso curioso:
	Asumamos que estamos en un directorio "test"
	En él hay un ARCHIVO "file" y un DIRECTORIO "dir"
	Si hacemos:
	dir/
	bash: dir/: is a directory
	$? = 126
	Y si hacemos:
	file/
	bash: file/: Not a directory
	$? = 126

O sea, bash se queja si hacemos dir/ por que en este contexto se espera un
comando o un archivo.
Y si hacemos file/, bash se queja por que la sintaxis <name>/ es para 
directorios y file no es un directorio.
En resumen, se queja siempre, pero por motivos distintos.

Si hacemos <archivo que no existe>/ entonces da el clásico
bash: <archivo que no existe>/: No such file or directory
$? = 127
*/

static char	*find_as_path(char *cmd, char *cmderror, int *exit_status);
static char	*find_in_path(char *cmd, int *exit_status, t_ms *ms);
char		**get_path_directories(t_env *env); // aun no static por que habrá que moverlo maybe
static char	*get_file_in_directory(char *filename, int *exit_status, char *dir);
static char	*find_in_pwd(char *cmd, int *exit_status);

/* Devuelve el programa representado por la string cmd y gestiona errores de 
ejecución previos asignando si es necesario exit_status a un valor. */
char	*find_program(char *cmd, int *exit_status, t_ms *ms)
{
	char	*program; 

	// if (!cmd)
	//	no debería ocurrir nunca esto
	if (ft_strchr(cmd, '/'))
		return (find_as_path(cmd, NULL, exit_status));
	program = find_in_path(cmd, exit_status, ms);
	if (program || *exit_status != 0) // creo que bien
		return (program);
	program = find_in_pwd(cmd, exit_status);
	if (program || *exit_status != 0)
		return (program);
	return (program); // redundante
}

/* Asumiendo que cmd representa un archivo válido, comprueba si el mismo existe 
y gestiona errores como si es un directorio, si el archivo no existe, o si el 
archivo encontrado no tiene permisos de ejecución. */
static char	*find_as_path(char *cmd, char *cmderror, int *exit_status)
{
	if (!cmderror)
		cmderror = cmd;
	if (access(cmd, F_OK) == SUCCESS) // el archivo EXISTE
	{
		if (is_directory(cmd))
		{
			*exit_status = _IS_DIR;
			exec_error(cmderror, IS_DIR);
		}
		else if (is_file(cmd))
		{
			if (access(cmd, X_OK) == SUCCESS)
				return (cmd);
			*exit_status = _PERMISSION_DENIED;
			exec_error(cmderror, PERMISSION_DENIED);
		}
		else
			exec_error(cmd, "Archivo raro?"); // provisional
	}
	else
	{
		*exit_status = _NO_SUCH_FILE;
		exec_error(cmderror, NO_SUCH_FILE);
	}
	return (NULL);
}

/* Gestiona la búsqueda de un comando cmd en los directorios indicados por la 
variable de entorno PATH y gestiona los posibles errores. */
static char	*find_in_path(char *cmd, int *exit_status, t_ms *ms)
{
	char	*filepath;
	char	**path_dir;
	int		i;

	path_dir = get_path_directories(ms->env);
	if (!path_dir)
		return (NULL);
	i = 0;
	while (path_dir[i])
	{
		filepath = get_file_in_directory(cmd, exit_status, path_dir[i]);
		if (filepath || *exit_status != 0) // creo que todo bien pero dejo esto aquí de momento
		{
			free_array(path_dir);
			return (filepath);
		}
		i++;
	}
	free_array(path_dir);
	*exit_status = _CMD_NOT_FOUND;
	exec_error(cmd, CMD_NOT_FOUND);
	return (NULL);
}

/* Obtiene la lista de directorios indicados por PATH */
char	**get_path_directories(t_env *env)
{
	t_env	*path_env;
	char	**path_split;

	path_env = env_find("PATH", env);
	if (!path_env || !path_env->content || !path_env->content[0])
		return (NULL);
	path_split = ft_split(path_env->content, ':');
	if (!path_split)
		ms_quit(MALLOC_ERR);
	return (path_split);
}

/* Obtiene el archivo filename en el directorio dir y gestiona errores y casos 
especificos. Esta función está diseñada para ser usada por find_in_path() */
static char	*get_file_in_directory(char *filename, int *exit_status, char *dir)
{
	char	*filepath;

	if (ft_strchr(dir, '*')) // si hay wildcards en este directorio, skip (CREO)
		return (NULL);
	filepath = join_filename(filename, dir);
	if (dir[0] != '/')
		return (find_as_path(filepath, NULL, exit_status)); // direcciones relativas en el path HABRÁ QUE VER SI ESTO VA
	if (access(filepath, F_OK) == SUCCESS) // si el archivo existe
	{
		if (is_file(filepath))
		{
			if (access(filepath, X_OK) == SUCCESS) // tiene permisos de ejecución
				return (filepath);
			*exit_status = _PERMISSION_DENIED;
			exec_error(filepath, PERMISSION_DENIED);
		}			
		else if (!is_directory(filepath))
			exec_error(filepath, "Archivo raro?"); // provisional
	}
	free(filepath);
	return (NULL);
}

/* Gestiona la búsqueda del archivo indicado por cmd en el directorio actual, 
cosa que minishell hará si no tiene un PATH válido. También gestiona errores 
varios como si el directorio actual ya no existe por que fue eliminado como 
si el archivo buscado no existe, etc. */
static char	*find_in_pwd(char *cmd, int *exit_status) // CREO?
{
	char	*filepath;
	char	*finalpath;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		*exit_status = _NO_SUCH_FILE;
		exec_error(cmd, NO_SUCH_FILE);
		return (NULL);
	}
	filepath = join_filename(cmd, pwd);
	free(pwd);
	finalpath = find_as_path(filepath, cmd, exit_status);
	free(filepath);
	return (finalpath);
}
