/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_filepath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:35:49 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/12 14:01:54 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TO-DO:

*/

// static char	*find_as_path(char *cmd, int *exit_status);
static char	*find_as_command(char *cmd, int *exit_status, t_ms *ms);
static char	**get_path_directories(t_env *env);
static char	*find_locally(char *cmd, int *exit_status);
static char	*find_as_a_path(char *file_path, int *exit_status);

/* Devuelve el file_path al programa representado por la string cmd y gestiona
errores de ejecución previos asignando un valor a exit_status */
char	*command_to_file_path(char *cmd, int *exit_status, t_ms *ms)
{
	char	*file_path;

	if (!ft_strchr(cmd, '/'))
	{
		file_path = find_as_command(cmd, exit_status, ms);
		if (file_path || *exit_status != 0)
			return (file_path);
	}
	file_path = find_as_a_path(cmd, exit_status);
	if (file_path || *exit_status != 0)
		return (file_path);
	file_path = find_locally(cmd, exit_status);
	if (file_path || *exit_status != 0)
		return (file_path);
	return (NULL);
}

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
	i = 0;
	while (directories[i] != NULL)
	{
		file_path = join_filename(cmd, directories[i]);
		if (file_check(file_path, IS_FILE) && \
		(ft_strcmp(".", cmd) && ft_strcmp("..", cmd)))
		{
			if (!file_check(file_path, X_OK))
				*exit_status = exec_error(cmd, PERM_DENIED, _PERM_DENIED);
			free_array(directories);
			return (file_path);
		}
		free(file_path);
		i++;
	}
	*exit_status = exec_error(cmd, CMD_NOT_FOUND, _CMD_NOT_FOUND);
	free_array(directories);
	return (NULL);
}

/* Obtiene la lista de directorios indicados por PATH */
static char	**get_path_directories(t_env *env)
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

/* Gestiona la búsqueda del archivo indicado por cmd en el directorio actual,
cosa que minishell hará si no tiene un PATH válido. También gestiona errores
varios como si el directorio actual ya no existe por que fue eliminado como
si el archivo buscado no existe, etc. */
static char	*find_locally(char *cmd, int *exit_status)
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
		else if (!file_check(file_path, X_OK))
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
que interpretar literalmente como path absoluto o relativo. */
static char	*find_as_a_path(char *file_path, int *exit_status)
{
	if (file_check(file_path, IS_DIRECTORY))
		*exit_status = exec_error(file_path, IS_DIR, _IS_DIR);
	else if (file_check(file_path, IS_FILE))
	{
		if (file_path[ft_strlen(file_path) - 1] == '/')
			*exit_status = exec_error(file_path, NOT_DIR, _NOT_DIR);
		else if (!file_check(file_path, X_OK))
			*exit_status = exec_error(file_path, PERM_DENIED, _PERM_DENIED);
		else
			return (file_path);
	}
	if (!file_check(file_path, FILE_EXISTS))
		*exit_status = exec_error(file_path, NO_SUCH_FILE, _NO_SUCH_FILE);
	return (NULL);
}
