/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_filepath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:35:49 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/25 16:24:31 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_as_command(char *cmd, int *exit_status, t_ms *ms);
static char	**get_path_directories(t_env *env);
static char	*find_as_pathname(char *pathname, int *exit_status);

/* Devuelve el file_path al programa representado por la string cmd y gestiona
errores de ejecución previos asignando un valor a exit_status */
char	*get_pathname(char *cmd, int *exit_status, t_ms *ms)
{
	char	*pathname;
	int		xs;

	xs = 0;
	if (!cmd)
		return (NULL);
	if (!ft_strchr(cmd, '/'))
	{
		pathname = find_as_command(cmd, &xs, ms);
		if (xs != 0)
			*exit_status = xs;
		if (pathname || xs != 0)
			return (pathname);
	}
	pathname = find_as_pathname(cmd, exit_status);
	if (pathname || *exit_status != 0)
		return (pathname);
	free(pathname);
	return (NULL);
}

/* Gestiona la búsqueda de un comando cmd en los directorios indicados por la
variable de entorno PATH y gestiona los posibles errores. */
static char	*find_as_command(char *cmd, int *exit_status, t_ms *ms)
{
	char	*pathname;
	char	**pathdirs;
	int		i;

	pathdirs = get_path_directories(ms->env);
	if (!pathdirs)
		return (NULL);
	i = 0;
	while (pathdirs[i] != NULL)
	{
		pathname = join_filename(cmd, pathdirs[i]);
		if ((file_check(pathname, IS_FILE) || file_check(pathname, IS_LINK)) && \
		(ft_strcmp(".", cmd) && ft_strcmp("..", cmd)))
		{
			if (file_check(pathname, X_OK) == FALSE)
				*exit_status = exec_error(cmd, PERM_DENIED, _PERM_DENIED);
			ft_free_array(pathdirs);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	*exit_status = exec_error(cmd, CMD_NOT_FOUND, _CMD_NOT_FOUND);
	ft_free_array(pathdirs);
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

/* Esta función asume que cmd ya está formateado como una dirección que hay
que interpretar literalmente como path absoluto o relativo. */
static char	*find_as_pathname(char *pathname, int *exit_status)
{
	char	*clean_pathname;

	clean_pathname = remove_slashes(pathname);
	if (file_check(clean_pathname, IS_DIRECTORY) == TRUE)
		*exit_status = exec_error(pathname, IS_DIR, _IS_DIR);
	else if (file_check(clean_pathname, IS_FILE) == TRUE || \
	file_check(clean_pathname, IS_LINK) == TRUE)
	{
		if (pathname[ft_strlen(pathname) - 1] == '/')
			*exit_status = exec_error(pathname, NOT_DIR, _NOT_DIR);
		else if (!file_check(clean_pathname, X_OK))
			*exit_status = exec_error(pathname, PERM_DENIED, _PERM_DENIED);
		else
		{
			free(clean_pathname);
			return (pathname);
		}
	}
	else if (file_check(clean_pathname, F_OK) == FALSE)
		*exit_status = exec_error(pathname, NO_SUCH_FILE, _NO_SUCH_FILE);
	else
		*exit_status = exec_error(pathname, UNSUPPORTED_FILE, 1);
	free(clean_pathname);
	return (NULL);
}
