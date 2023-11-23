/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_filepath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:35:49 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/23 17:25:34 by apresas-         ###   ########.fr       */
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

	-CORREGIDO (en principio)

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

// static char	*find_as_path(char *cmd, int *exit_status);
static char	*find_as_command(char *cmd, int *exit_status, t_ms *ms);
char		**get_path_directories(t_env *env); // aun no static por que habrá que moverlo maybe
static char	*find_as_relative_path(char *cmd, int *exit_status);
static char	*find_as_absolute_path(char *file_path, int *exit_status);

/* Devuelve el programa representado por la string cmd y gestiona errores de 
ejecución previos asignando si es necesario exit_status a un valor. */
char	*command_to_file_path(char *cmd, int *exit_status, t_ms *ms)
{
	char	*file_path; 

	if (!ft_strchr(cmd, '/'))
	{
		file_path = find_as_command(cmd, exit_status, ms);
		if (file_path || *exit_status != 0) // creo que bien
			return (file_path);
	}
	file_path = find_as_absolute_path(cmd, exit_status);
	if (file_path || *exit_status != 0)
		return (file_path);
	file_path = find_as_relative_path(cmd, exit_status);
	if (file_path || *exit_status != 0)
		return (file_path);
	return (NULL);
}

/* Asumiendo que cmd representa un archivo válido, comprueba si el mismo existe 
y gestiona errores como si es un directorio, si el archivo no existe, o si el 
archivo encontrado no tiene permisos de ejecución. */
// static char	*find_as_path(char *cmd, int *exit_status)
// {
// 	if (access(cmd, F_OK) == SUCCESS) // el archivo EXISTE
// 	{
// 		printf("HOLA QUE TAL COMO ESTAS NOSEQUE\n");
// 		if (is_directory(cmd))
// 			*exit_status = exec_error(cmd, IS_DIR, _IS_DIR);
// 		else if (is_file(cmd))
// 		{
// 			if (cmd[ft_strlen(cmd) - 1] == '/')
// 				*exit_status = exec_error(cmd, NOT_DIR, _NOT_DIR);
// 			if (access(cmd, HAS_EXECUTE_PERMISSIONS) == SUCCESS)
// 				return (cmd);
// 			*exit_status = exec_error(cmd, PERM_DENIED, _PERM_DENIED);
// 		}
// 		else
// 			exec_error(cmd, "Archivo raro?", 1); // provisional
// 	}
// 	else
// 		*exit_status = exec_error(cmd, NO_SUCH_FILE, _NO_SUCH_FILE);
// 	return (NULL);
// }

/* Gestiona la búsqueda de un comando cmd en los directorios indicados por la 
variable de entorno PATH y gestiona los posibles errores. */
static char	*find_as_command(char *cmd, int *exit_status, t_ms *ms)
{
	char	*file_path;
	char	**directories;
	int		i;

	directories = get_path_directories(ms->env);
	if (!directories)
		return (NULL);
	i = -1;
	while (directories[++i] != NULL)
	{
		file_path = join_filename(cmd, directories[i]);
		if (access(file_path, FILE_EXISTS) == SUCCESS && is_file(file_path) && \
		(ft_strcmp(".", cmd) && ft_strcmp("..", cmd)))
		{
			if (access(file_path, HAS_EXECUTE_PERMISSIONS) == FAILURE)
				*exit_status = exec_error(cmd, PERM_DENIED, _PERM_DENIED);
			free_array(directories);
			return (file_path);
		}
		free(file_path);
	}
	*exit_status = exec_error(cmd, CMD_NOT_FOUND, _CMD_NOT_FOUND);
	free_array(directories);
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
especificos. Esta función está diseñada para ser usada por find_as_command() */
// static char	*get_file_in_directory(char *filename, int *exit_status, char *dir)
// {
// 	char	*file_path;

// 	// if (ft_strchr(dir, '*')) // wildcards, que hago? puede haber * en un file si se escapa el * como \* creo.
// 		// return (NULL);
// 	file_path = join_filename(filename, dir);
// 	if (access(file_path, FILE_EXISTS) == SUCCESS)
// 	{
// 		if (is_file(file_path))
// 		{
// 			if (access(file_path, HAS_EXECUTE_PERMISSIONS) == SUCCESS) // tiene permisos de ejecución
// 				return (file_path);
// 			*exit_status = exec_error(file_path, PERM_DENIED, _PERM_DENIED);
// 		}			
// 		else if (!is_directory(file_path))
// 			exec_error(file_path, "Archivo raro?", 1); // provisional
// 	}
// 	free(file_path);
// 	return (NULL);
// }

/* Gestiona la búsqueda del archivo indicado por cmd en el directorio actual, 
cosa que minishell hará si no tiene un PATH válido. También gestiona errores 
varios como si el directorio actual ya no existe por que fue eliminado como 
si el archivo buscado no existe, etc. */
static char	*find_as_relative_path(char *cmd, int *exit_status) // TEST THOROUGHLY
{
	char	*file_path;
	char	*pwd;

	pwd = safe_getcwd(cmd, exit_status);
	if (!pwd)
		return (NULL);
	file_path = join_filename(cmd, pwd);
	free(pwd);
	if (file_check(file_path, IS_DIRECTORY))
		*exit_status = exec_error(cmd, IS_DIR, _IS_DIR);
	else if (file_check(file_path, IS_FILE))
	{
		if (file_path[ft_strlen(cmd) - 1] == '/')
			*exit_status = exec_error(cmd, NOT_DIR, _NOT_DIR);
		else if (!file_check(file_path, HAS_EXECUTE_PERMISSIONS))
			*exit_status = exec_error(cmd, PERM_DENIED, _PERM_DENIED);
		else
			return (file_path);
	}
	if (!file_check(file_path, FILE_EXISTS))
		*exit_status = exec_error(cmd, NO_SUCH_FILE, _NO_SUCH_FILE);
	free(file_path);
	return (NULL);
}

/* Esta función asume que cmd ya está formateado como una dirección que hay 
que interpretar literalmente como path absoluto. */
static char	*find_as_absolute_path(char *file_path, int *exit_status)
{
	// Ocurre el tema de NOT_DIR y IS_DIR
	if (file_check(file_path, IS_DIRECTORY))
		*exit_status = exec_error(file_path, IS_DIR, _IS_DIR);
	else if (file_check(file_path, IS_FILE))
	{
		if (file_path[ft_strlen(file_path) - 1] == '/')
			*exit_status = exec_error(file_path, NOT_DIR, _NOT_DIR);
		else if (file_check(file_path, HAS_EXECUTE_PERMISSIONS))
			*exit_status = exec_error(file_path, PERM_DENIED, _PERM_DENIED);
		else
			return (file_path);
	}
	if (!file_check(file_path, FILE_EXISTS))
		*exit_status = exec_error(file_path, NO_SUCH_FILE, _NO_SUCH_FILE);
	return (NULL);
}

// char	*find_file_in_directory(char *filename, char *dirpath)
// {
// 	char	*filepath;

// 	filepath = join_filename(filename, dirpath);
// 	if (ft_strrchr(filepath, '/') == ft_strlen(filepath) - 1) // file is formatted as directory
// 	{
// 		exec_error(filename, IS_DIR);
// 		*exit_status = _IS_DIR;
// 		return (NULL);
// 	}
// 	if (access(filepath, F_OK) == SUCCESS) // File exists
// 	{

// 	}
// }

/*
UNA VEZ EL ARCHIVO HAYA SIDO ENCONTRADO
	Se comprueba esto:
		Si el formato con el que has buscado el archivo representa un directorio, por ejemplo:
			Encuentras un archivo llamado "file", pero tú introduciste "file/"
			Entonces "Not a directory" $? = 126
		Si el formato con el que has buscado el archivo representa un archivo, pero el archivo
		encontrado es un directorio, por ejemplo:
			Encuentras un directorio llamado "dir", pero tú lo buscaste como "dir/"
			Entonces "Is a directory" $? = 126

A estos dos procesos solo se puede llegar si has introducido un '/' en el nombre.
*/