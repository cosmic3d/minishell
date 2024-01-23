/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:02:32 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/23 16:47:39 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_arg_errors(char *arg);
static char	*crop_pathname(char *oldpath);
static int	update_environment(t_ms *ms, char *new_pwd);
static int	dumb_error(t_ms *ms, char *arg);

/* Función que emula el builtin cd */
int	ms_cd(t_ms *ms, char **argv)
{
	char	*pwd;

	if (argv[1] == NULL || !argv[1][0])
		return (EXIT_SUCCESS);
	if (ft_strlen(argv[1]) >= 256)
		return (ms_perror("cd", argv[1], TOO_LONG, NULL));
	if (check_arg_errors(argv[1]) == FAILURE)
		return (EXIT_FAILURE);
	if (chdir(argv[1]) == -1)
		return (ms_perror("cd", "chdir", strerror(errno), NULL));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (dumb_error(ms, argv[1]));
	if (update_environment(ms, pwd) == FAILURE)
		return (-1);
	return (EXIT_SUCCESS);
}

static int	dumb_error(t_ms *ms, char *arg)
{
	int		i;
	char	*new_pwd;

	i = 0;
	new_pwd = ms->pwd;
	ms_perror("cd", ERROR_RETRIEVE, strerror(errno), NULL);
	while (arg[i] != '\0')
	{
		if (arg[i] != '.' && arg[i] != '/')
			break ;
		i++;
	}
	if (arg[i] == '\0' && i != 0)
	{
		new_pwd = join_filename(arg, ms->pwd);
		if (!new_pwd)
			ms_quit(MALLOC_ERR);
	}
	update_environment(ms, new_pwd);
	return (FAILURE);
}

static int	check_arg_errors(char *arg)
{
	char	*pathname;

	if (file_check(arg, F_OK) == TRUE)
	{
		if (file_check(arg, F_DIR) == FALSE)
			return (ms_perror("cd", arg, NOT_DIR, NULL));
		if (file_check(arg, X_OK) == FALSE)
			return (ms_perror("cd", arg, PERM_DENIED, NULL));
		return (SUCCESS);
	}
	pathname = ft_strdup(arg);
	if (!pathname)
		ms_quit(MALLOC_ERR);
	while (42)
	{
		/* FALTA LIBERAR PATHNAME */
		pathname = crop_pathname(pathname);
		if (file_check(pathname, F_OK) == TRUE)
		{
			if (file_check(pathname, F_DIR) == FALSE)
				return (ms_perror("cd", arg, NOT_DIR, NULL));
			return (ms_perror("cd", arg, NO_SUCH_FILE, NULL));
		}
		if (ft_strchr(pathname, '/') == NULL) // no quedan '/'
			return (ms_perror("cd", arg, NO_SUCH_FILE, NULL));
	}
}

static char	*crop_pathname(char *oldpath)
{
	char	*newpath;
	int		newlen;

	if (ft_strrchr(oldpath, '/') == NULL)
		return (oldpath);
	newlen = ft_strrchr(oldpath, '/') - oldpath;
	newpath = ft_strndup(oldpath, newlen);
	if (!newpath)
		ms_quit(MALLOC_ERR);
	free(oldpath);
	return (newpath);
}

static int	update_environment(t_ms *ms, char *new_pwd)
{
	t_env	*pwd;
	t_env	*oldpwd;

	if (ms->oldpwd)
		free(ms->oldpwd);
	ms->oldpwd = ms->pwd;
	ms->pwd = new_pwd;
	pwd = env_find("PWD", ms->env);
	oldpwd = env_find("OLDPWD", ms->env);
	if (!oldpwd && pwd && env_add("OLDPWD", pwd->content, &ms->env) == FAILURE)
		return (FAILURE);
	else if (!oldpwd && !pwd && env_add("OLDPWD", ms->oldpwd, &ms->env) == FAILURE)
		return (FAILURE);
	else if (oldpwd && pwd && env_edit(oldpwd, pwd->content) == FAILURE)
		return (FAILURE);
	else if (oldpwd && !pwd && env_edit(oldpwd, ms->pwd) == FAILURE)
		return (FAILURE);
	if (pwd && env_edit(pwd, ms->pwd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
