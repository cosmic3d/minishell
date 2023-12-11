/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_process_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:00:43 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/11 17:05:36 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_new(char *name, char *arg, t_ms *ms);
static int	export_equal(t_env *var, char *arg);
static int	export_add(t_env *var, char *arg);

int	process_argument(char *arg, t_ms *ms)
{
	t_env	*var;
	char	*name;
	int		op;

	name = get_name(arg);
	if (!name)
		return (FAILURE);
	op = get_operation(arg);
	var = env_find(name, ms->env);
	if (!var && export_new(name, arg, ms) == FAILURE)
	{
		free(name);
		return (FAILURE);
	}
	free(name);
	if (var && (op == '=' && export_equal(var, arg) == FAILURE))
		return (FAILURE);
	else if (var && (op == '+' && export_add(var, arg) == FAILURE))
		return (FAILURE);
	return (SUCCESS);
}

static char	*get_name(char *arg)
{
	char	*name;
	int		len;
	int		i;

	len = 0;
	while (arg[len] && arg[len] != '+' && arg[len] != '=')
		len++;
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
	{
		ms_perror("malloc", strerror(errno), NULL, NULL);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		name[i] = arg[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static int	get_operation(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=' && arg[i] != '+')
		i++;
	if (arg[i] == '+')
		return ('+');
	else if (arg[i] == '=')
		return ('=');
	else if (arg[i] == '\0')
		return (0);
	return (0);
}

static int	export_new(char *name, char *arg, t_ms *ms)
{
	char	*content;

	content = get_content(arg);
	if (errno)
		return (FAILURE);
	if (env_add(name, content, &ms->env) == FAILURE)
	{
		free(content);
		return (FAILURE);
	}
	if (content)
		free(content);
	return (SUCCESS);
}

static int	export_equal(t_env *var, char *arg)
{
	char	*new_content;

	new_content = get_content(arg);
	if (errno)
		return (FAILURE);
	if (var->content)
		free(var->content);
	var->content = new_content;
	return (SUCCESS);
}

static int	export_add(t_env *var, char *arg)
{
	char	*arg_content;
	char	*joined_content;

	arg_content = get_content(arg);
	if (errno)
		return (FAILURE);
	if (var->content)
	{
		joined_content = ft_strjoin(var->content, arg_content);
		if (!joined_content)
		{
			free(arg_content);
			return (ms_perror("malloc", strerror(errno), NULL, NULL));
		}
		free(var->content);
		free(arg_content);
		var->content = joined_content;
	}
	else
		var->content = arg_content;
	return (SUCCESS);
}
