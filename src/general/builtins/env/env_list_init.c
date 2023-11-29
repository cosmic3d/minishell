/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:08:12 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/20 18:04:50 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		no_envp_case(t_ms *ms);
static t_env	*env_get_envp(char **envp, t_env *head);
static int		get_envp_values(char **name, char **content, char *envp_line);
static t_env	*env_update_list(t_env *env);

/* Esta función inicializa la lista de variables del entorno en base a **envp
que recibe minishell en el main.
Gestiona la posibilidad de que envp sea NULL de un modo u otro. */
void	env_list_init(t_ms *ms, char **envp)
{
	t_env	*env;

	env = NULL;
	if (!envp || !envp[0]) // NULL case
	{
		if (no_envp_case(ms) == FAILURE)
		{
			free_env_list(ms);
			return (FAILURE);
		}
		return (SUCCESS);
	}
	if (check_envp_syntax(envp) == FAILURE)
	{
		
	}
	env = env_get_envp(envp, env);
	env = env_update_list(env); // TODO NEXT
	ms->env = env;
	ms->pwd = getcwd(NULL, 0);
	if (!ms->pwd)
	{
		ms_perror("getcwd", strerror(errno), NULL, NULL);
		exit(EXIT_FAILURE);
	}
	ms->exit_status = 0;
	return ;
}

static int	no_envp_case(t_ms *ms)
{
	ms->pwd = getcwd(NULL, 0);
	if (!ms->pwd)
	{
		ms_perror("getcwd", strerror(errno), NULL, NULL);
		return (FAILURE);
	}
	if (env_add("SHLVL", "1", &ms->env))
		return (FAILURE);
	if (env_add("OLDPWD", NULL, &ms->env))
		return (FAILURE);
	if (env_add("PWD", ms->pwd, &ms->env))
		return (FAILURE);
	return (SUCCESS);
}

static t_env	*env_get_envp(char **envp, t_env *head)
{
	char	*name;
	char	*content;
	int		i;

	i = 0;
	name = NULL;
	content = NULL;
	while (envp[i])
	{
		if (get_envp_values(&name, &content, envp[i]))
			exit(EXIT_FAILURE);
		if (env_add(name, content, &head))
			exit(EXIT_FAILURE);
		free(name);
		free(content);
		i++;
	}
	return (head);
}

static int	get_envp_values(char **name, char **content, char *envp_line)
{
	int	eq_i;

	eq_i = ft_strchr_i(envp_line, '=');
	if (eq_i == -1)
	{
		write(1, "STRCHR_I ERROR\n", 16); // Esto en principio no ocurrirá
		exit(EXIT_FAILURE);
	}
	*name = ft_substr(envp_line, 0, eq_i);
	if (!*name)
	{
		ms_error(MALLOC_ERR);
		return (FAILURE);
	}
	*content = ft_substr(envp_line, eq_i + 1, ft_strlen(envp_line) - eq_i);
	if (!*content)
	{
		ms_error(MALLOC_ERR);
		free(name);
		return (FAILURE);
	}
	return (SUCCESS);
}

/* Esta función actualiza SHLVL 
Quizá hago que actualize PWD también más adelante. */
static t_env	*env_update_list(t_env *env)
{
	t_env	*aux;
	int		shlvl;

	aux = env_find("SHLVL", env);
	shlvl = ft_atoi(aux->content) + 1;
	free(aux->content);
	if (shlvl >= 1000)
	{
		printf(SHLVL_WARNING, shlvl);
		shlvl = 1;
	}
	aux->content = ft_itoa(shlvl);
	if (!aux->content)
	{
		ms_error(MALLOC_ERR);
		exit(EXIT_FAILURE);
	}
	return (env);
}
