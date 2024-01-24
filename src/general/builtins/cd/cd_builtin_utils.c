/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:29:28 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/24 17:25:43 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*set_dst(t_ms *ms, char **argv, int *flag)
{
	char	*arg;
	char	*dst;

	arg = argv[1];
	if (arg && ft_strcmp(arg, "--") == 0)
		arg = argv[2];
	if (!arg)
		dst = cd_home(ms);
	else if (arg && ft_strcmp(arg, "-") == 0)
		dst = cd_oldpwd(ms, flag);
	else if (arg && !arg[0])
	{
		*flag |= 2;
		dst = arg;
	}
	else
		dst = arg;
	return (dst);
}

char	*cd_home(t_ms *ms)
{
	t_env	*home_var;
	char	*dst;

	home_var = env_find("HOME", ms->env);
	if (!home_var || !home_var->content)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (NULL);
	}
	dst = ft_strdup(home_var->content);
	if (!dst)
		ms_quit(MALLOC_ERR);
	return (dst);
}

char	*cd_oldpwd(t_ms *ms, int *flag)
{
	char	*arg;
	t_env	*oldpwd_var;

	oldpwd_var = env_find("OLDPWD", ms->env);
	if (!oldpwd_var || !oldpwd_var->content)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		return (NULL);
	}
	arg = ft_strdup(oldpwd_var->content);
	if (!arg)
		ms_quit(MALLOC_ERR);
	*flag |= 1;
	return (arg);
}

int	update_environment(t_ms *ms, char *new_pwd)
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
		ms_quit(MALLOC_ERR);
	else if (!oldpwd && !pwd \
	&& env_add("OLDPWD", ms->oldpwd, &ms->env) == FAILURE)
		ms_quit(MALLOC_ERR);
	else if (oldpwd && pwd && env_edit(oldpwd, pwd->content) == FAILURE)
		ms_quit(MALLOC_ERR);
	else if (oldpwd && !pwd && env_edit(oldpwd, ms->pwd) == FAILURE)
		ms_quit(MALLOC_ERR);
	if (pwd && env_edit(pwd, ms->pwd) == FAILURE)
		ms_quit(MALLOC_ERR);
	return (SUCCESS);
}
