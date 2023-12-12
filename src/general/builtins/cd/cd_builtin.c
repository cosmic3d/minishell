/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:02:32 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/12 15:57:55 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_arg_errors(char *arg);
static int	update_environment(t_ms *ms, char *new_pwd);

/* Función que emula el builtin cd */
int	ms_cd(t_ms *ms, char **argv)
{
	char	*pwd;

	if (argv[1] == NULL || !argv[1][0])
		return (EXIT_SUCCESS);
	if (check_arg_errors(argv[1]) == FAILURE)
		return (EXIT_FAILURE);
	if (chdir(argv[1]) == -1)
		return (ms_perror("cd", "chdir", strerror(errno), NULL));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ms_perror("cd", "chdir", strerror(errno), NULL));
	if (update_environment(ms, pwd) == FAILURE)
		return (-1);
	if (ms->pwd)
		free(ms->pwd);
	ms->pwd = ft_strdup(pwd);
	if (!ms->pwd)
	{
		ms_perror("malloc", strerror(errno), NULL, NULL);
		return (-1);
	}
	return (EXIT_SUCCESS);
}

static int	check_arg_errors(char *arg)
{
	if (file_check(arg, FILE_EXISTS) == FALSE)
		return (ms_perror("cd", arg, NO_SUCH_FILE, NULL));
	if (file_check(arg, IS_DIRECTORY) == FALSE)
		return (ms_perror("cd", arg, NOT_DIR, NULL));
	if (file_check(arg, X_OK) == FALSE)
		return (ms_perror("cd", arg, PERM_DENIED, NULL));
	return (SUCCESS);
}

static int	update_environment(t_ms *ms, char *new_pwd)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = env_find("PWD", ms->env);
	if (!pwd)
	{
		if (env_add("PWD", NULL, &ms->env))
			return (FAILURE);
		pwd = env_find("PWD", ms->env);
	}
	oldpwd = env_find("OLDPWD", ms->env);
	if (!oldpwd)
	{
		if (env_add("OLDPWD", NULL, &ms->env))
			return (FAILURE);
		oldpwd = env_find("OLDPWD", ms->env);
	}
	if (oldpwd->content)
		free(oldpwd->content);
	oldpwd->content = pwd->content;
	pwd->content = new_pwd;
	return (SUCCESS);
}
