/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:02:32 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/25 19:09:14 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_arg_errors(char *arg);
static int	check_arg_errors_2(char *pathname, char *arg);
static char	*crop_pathname(char *oldpath);
static int	dumb_error(t_ms *ms, char *arg);

/* Función que emula el builtin cd */
int	ms_cd(t_ms *ms, char **argv)
{
	char	*pwd;
	char	*dst;
	int		flag;

	flag = 0;
	dst = set_dst(ms, argv, &flag);
	if (!dst)
		return (FAILURE);
	if (ft_strlen(dst) >= 256)
		return (ms_perror("cd", dst, TOO_LONG, NULL));
	if (!(flag & 2) && check_arg_errors(dst) == FAILURE)
		return (FAILURE);
	if (!(flag & 2) && chdir(dst) == -1)
		return (ms_perror("cd", "chdir", strerror(errno), NULL));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (dumb_error(ms, dst));
	update_environment(ms, pwd);
	if (flag & 1)
		printf("%s\n", pwd);
	return (SUCCESS);
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
		if (file_check(arg, IS_DIRECTORY) == FALSE)
			return (ms_perror("cd", arg, NOT_DIR, NULL));
		if (file_check(arg, X_OK) == FALSE)
			return (ms_perror("cd", arg, PERM_DENIED, NULL));
		return (SUCCESS);
	}
	pathname = ft_strdup(arg);
	if (!pathname)
		ms_quit(MALLOC_ERR);
	return (check_arg_errors_2(pathname, arg));
}

static int	check_arg_errors_2(char *pathname, char *arg)
{
	while (42)
	{
		pathname = crop_pathname(pathname);
		if (file_check(pathname, F_OK) == TRUE)
		{
			if (file_check(pathname, IS_DIRECTORY) == FALSE)
			{
				free(pathname);
				return (ms_perror("cd", arg, NOT_DIR, NULL));
			}
			free(pathname);
			return (ms_perror("cd", arg, NO_SUCH_FILE, NULL));
		}
		if (ft_strchr(pathname, '/') == NULL)
		{
			free(pathname);
			return (ms_perror("cd", arg, NO_SUCH_FILE, NULL));
		}
	}
	free(pathname);
	return (SUCCESS);
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
