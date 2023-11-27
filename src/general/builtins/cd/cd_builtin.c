/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:02:32 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/27 17:07:20 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg_errors(char *arg);
static void	cd_error(char *arg, char *error_str);
static void	update_environment(t_ms *ms, char *new_pwd);

/* Función que emula el builtin cd */
int	ms_cd(t_ms *ms, char **argv)
{
	char	*pwd;

	if (argv[1] == NULL || !argv[1][0])
		return (EXIT_SUCCESS);
	if (check_arg_errors(argv[1]) == FAILURE)
		return (EXIT_FAILURE);
	if (chdir(argv[1]) == -1)
	{
		cd_error(argv[1], "unable to change directory"); // for now
		return (EXIT_FAILURE);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		cd_error(argv[1], "error retrieving current directory"); // for now
		return (EXIT_FAILURE);
	}
	update_environment(ms, pwd);
	return (EXIT_SUCCESS);
}

void	update_environment(t_ms *ms, char *new_pwd)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = env_find("PWD", ms->env);
	if (!pwd)
	{
		if (env_add("PWD", "", &ms->env))
			ms_quit(MALLOC_ERR);
		pwd = env_find("PWD", ms->env);
	}
	oldpwd = env_find("OLDPWD", ms->env);
	if (!oldpwd)
	{
		if (env_add("OLDPWD", "", &ms->env))
			ms_quit(MALLOC_ERR);
		oldpwd = env_find("OLDPWD", ms->env);
	}
	free(oldpwd->content);
	oldpwd->content = pwd->content;
	pwd->content = new_pwd;
}

static int	check_arg_errors(char *arg)
{
	struct stat	file;

	if (access(arg, FILE_EXISTS) != SUCCESS)
	{
		cd_error(arg, NO_SUCH_FILE);
		return (FAILURE);
	}
	lstat(arg, &file);
	if (!S_ISDIR(file.st_mode))
	{
		cd_error(arg, NOT_DIR);
		return (FAILURE);
	}
	if (access(arg, HAS_EXECUTE_PERMISSIONS) != SUCCESS)
	{
		cd_error(arg, PERM_DENIED);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	cd_error(char *arg, char *error_str)
{
	write(2, "minishell: cd: ", 15);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, error_str, ft_strlen(error_str));
	write(2, "\n", 1);
}
