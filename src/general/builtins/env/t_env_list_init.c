/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_list_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:35:07 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/05 11:46:37 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	envp_to_t_env(t_ms *ms, char **envp);
static int	update_env_list(t_ms *ms);
static int	update_shlvl(t_ms *ms);
static int	update_pwd(t_ms *ms, char *pwd);

int	env_list_init(t_ms *ms, char **envp)
{
	ms->env = NULL;
	if (envp_to_t_env(ms, envp) == FAILURE)
	{
		free_env_list(ms);
		return (FAILURE);
	}
	if (update_env_list(ms) == FAILURE)
	{
		free_env_list(ms);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	envp_to_t_env(t_ms *ms, char **envp)
{
	int		i;
	int		div;
	t_env	*new;

	i = -1;
	while (envp[++i])
	{
		div = ft_strchr_i(envp[i], '=');
		if (div == -1 || div == 0)
			continue;
		new = env_new(&ms->env);
		if (!new)
			return (FAILURE);
		new->name = ft_substr(envp[i], 0, div);
		if (!new->name)
			return (ms_perror("malloc", strerror(errno), NULL, NULL));
		new->content = ft_substr(envp[i], div+1, ft_strlen(envp[i]) - (div+1));
		if (!new->content)
			return (ms_perror("malloc", strerror(errno), NULL, NULL));
	}
	return (SUCCESS);
}

static int	update_env_list(t_ms *ms)
{
	char	*pwd;

	if (update_shlvl(ms) == FAILURE)
		return (FAILURE);
	pwd = getcwd(NULL, 0);
	if (errno)
		return (ms_perror("getcwd", strerror(errno), NULL, NULL));
	if (update_pwd(ms, pwd) == FAILURE)
	{
		free(pwd);
		return (FAILURE);
	}
	ms->pwd = pwd;
	return (SUCCESS); // hay que testear bien todo esto
}

static int	update_shlvl(t_ms *ms)
{
	t_env	*var;
	int		shlvl;

	var = env_find("SHLVL", ms->env);
	if (!var)
		return (env_add("SHLVL", "1", &ms->env));
	// Hay que comprobar si SHLVL contiene caracteres no numericos, entonces SHLVL=1!
	shlvl = ft_atoi(var->content) + 1;
	if (shlvl == 1000)
		return (env_edit(var, ""));
	else if (shlvl < 0)
		shlvl = 0;
	else if (shlvl > 1000)
	{
		printf(SHLVL_WARNING, shlvl); // esto va STDOUT o STDERR ??
		shlvl = 1;
	}
	free(var->content);
	var->content = ft_itoa(shlvl);
	if (!var->content)
		return (ms_perror("malloc", strerror(errno), NULL, NULL));
	return (SUCCESS);
}

static int	update_pwd(t_ms *ms, char *pwd)
{
	t_env	*var;

	var = env_find("OLDPWD", ms->env);
	if (!var)
		if (env_add("OLDPWD", NULL, &ms->env) == FAILURE)
			return (FAILURE);
	var = env_find("PWD", ms->env);
	if (!var)
	{
		if (env_add("PWD", NULL, &ms->env) == FAILURE)
			return (FAILURE);
		var = env_find("PWD", ms->env);
		var->content = ft_strdup(pwd);
		if (!var->content)
			return (ms_perror("malloc", strerror(errno), NULL, NULL));
	}
	return (SUCCESS);
}
