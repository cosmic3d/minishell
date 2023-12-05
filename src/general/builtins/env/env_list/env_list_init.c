/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:17:52 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/05 19:17:29 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	envp_to_env_list(t_ms *ms, char **envp);
static int	update_shlvl(t_ms *ms);
static int	update_pwd(t_ms *ms);
static int	update_oldpwd(t_ms *ms);

int	env_list_init(t_ms *ms, char **envp)
{
	if (envp_to_env_list(ms, envp) == FAILURE)
	{
		// free list? or just exit?
		return (FAILURE);
	}
	if (update_shlvl(ms) == FAILURE)
	{
		return (FAILURE);
	}
	if (update_pwd(ms) == FAILURE)
	{
		return (FAILURE);
	}
	if (update_oldpwd(ms) == FAILURE)
	{
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	envp_to_env_list(t_ms *ms, char **envp)
{
	t_env	*new;
	int		i;
	int		name_len;
	int		content_len;

	i = -1;
	while (envp[++i])
	{
		if (ft_strchr(envp[i], '=') == NULL)
			continue ;
		name_len = ft_strchr(envp[i], '=') - envp[i];
		if (name_len == 0)
			continue ;
		new = env_new(&ms->env);
		if (!new)
			return (FAILURE);
		new->name = ft_substr(envp[i], 0, name_len);
		if (!new->name)
			return (ms_perror("malloc", strerror(errno), NULL, NULL));
		content_len = ft_strlen(envp[i]) - (name_len + 1);
		new->content = ft_substr(envp[i], name_len + 1, content_len);
		if (!new->content)
			return (ms_perror("malloc", strerror(errno), NULL, NULL));
	}
	return (SUCCESS);
}

// version mas top
static int	update_shlvl(t_ms *ms)
{
	t_env	*var;
	int		shlvl;
	char	*shlvl_str;

	var = env_find("SHLVL", ms->env);
	if (!var)
		return (env_add("SHLVL", "1", &ms->env));
	if (!ft_isint(var->content))
		return (env_edit(var, "1"));
	shlvl = ft_atoi(var->content);
	if (shlvl < 0)
		return (env_edit(var, "0"));
	else if (shlvl > 998)
	{
		printf(SHLVL_WARNING, shlvl); // ESTO VA EN STDOUT
		return (env_edit(var, "1"));
	}
	shlvl_str = ft_itoa(shlvl + 1);
	if (!shlvl_str)
		return (ms_perror("malloc", strerror(errno), NULL, NULL));
	free(var->content);
	var->content = shlvl_str;
	return (SUCCESS);
}

static int	update_pwd(t_ms *ms)
{
	t_env	*var;

	var = env_find("PWD", ms->env);
	if (!var)
		return (env_add("PWD", ms->pwd, &ms->env));
	var->content = ft_strdup(ms->pwd);
	if (!var->content)
		return (ms_perror("malloc", strerror(errno), NULL, NULL));
	return (SUCCESS);
}

static int	update_oldpwd(t_ms *ms)
{
	t_env	*var;

	var = env_find("OLDPWD", ms->env);
	if (!var)
		return (env_add("OLDPWD", NULL, &ms->env));
	if (var->content)
		free(var->content);
	var->content = NULL;
	return (SUCCESS);
}
