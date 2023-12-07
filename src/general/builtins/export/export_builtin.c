/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:08:42 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/07 20:30:54 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argument_syntax(char *arg);
int	process_argument(char *arg, t_ms *ms);
char	*get_name(char *arg);
int	edit_content(t_env *var, char *arg, int op);
char	*get_content(char *arg);
int	new_variable(char *name, char *arg, t_ms *ms);
int	get_operation(char *arg);
int	export_print(t_env *env, t_env *node, t_env *abc_min, char *prev);

int	ms_export(t_ms *ms, char **argv)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = SUCCESS;
	if (!argv[i])
		return (export_print(ms->env, ms->env, NULL, NULL)); // maybe
	while (argv[i])
	{
		if (argument_syntax(argv[i]) == FAILURE)
		{
			printf("MISCOLONDRIO\n"); // print error message
			exit_status = 1;
			continue;
		}
		if (process_argument(argv[i], ms) == FAILURE)
		{
			return (FAILURE);
		}
		i++;
	}
	return (exit_status);
}

////////////////
int	export_print(t_env *env, t_env *node, t_env *abc_min, char *prev)
{
	if (!env)
		return (SUCCESS);
	while (node)
	{
		if (!prev || ft_strlcmp(node->name, prev) < 0)
		{
			if (!abc_min || ft_strlcmp(node->name, abc_min->name) > 0)
				abc_min = node;
		}
		node = node->next;
	}
	if (abc_min)
	{
		export_print(env, env, NULL, abc_min->name);
		if (!ft_strcmp(abc_min->name, "_"))
			return (SUCCESS);
		printf("declare -x %s", abc_min->name);
		if (abc_min->content)
			printf("=\"%s\"", abc_min->content);
		printf("\n");
	}
	return (SUCCESS);
}
////////////////////

//

int	argument_syntax(char *arg)
{
	int	i;

	if (arg[0] == '\0' || ft_isdigit(arg[0]))
		return (FAILURE);
	i = 0;
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (FAILURE);
		i++;
	}
	if ((arg[i] == '+' && arg[i + 1] != '=') || i == 0)
		return (FAILURE);
	return (SUCCESS);
}

int	process_argument(char *arg, t_ms *ms)
{
	t_env	*new;
	char	*name;

	name = get_name(arg);
	if (!name)
		return (FAILURE);
	new = env_find(name, ms->env);
	if (new && get_operation(arg) != 0 && \
	edit_content(new, arg, get_operation(arg)) == FAILURE)
	{
		free(name);
		return (FAILURE);
	}
	else if (!new && new_variable(name, arg, ms) == FAILURE)
	{
		free(name);
		return (FAILURE);
	}
	free(name);
	return (SUCCESS);
}

char	*get_name(char *arg)
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

int	edit_content(t_env *var, char *arg, int op)
{
	char	*new_content;
	char	*aux;

	new_content = get_content(arg);
	if (errno)
		return (FAILURE);
	if (op == '=' && env_edit(var, new_content) == FAILURE)
	{
		free(new_content);
		return (FAILURE);
	}
	else if (op == '+')
	{
		aux = ft_strjoin(var->content, new_content);
		if (!aux)
		{
			free(new_content);
			return (ms_perror("malloc", strerror(errno), NULL, NULL));
		}
		free(var->content);
		var->content = aux;
	}
	if (new_content)
		free(new_content);
	return (SUCCESS);
}

char	*get_content(char *arg)
{
	char	*content;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '\0')
		return (NULL);
	i++;
	// if (arg[i] == '\0') // necesario? testear
	// {
	// 	content = ft_strdup("");
	// 	if (!content)
	// 	{
	// 		ms_perror("malloc", strerror(errno), NULL, NULL);
	// 		return (NULL);
	// 	}
	// 	return (content);
	// }
	// testear
	content = ft_substr(arg, i, ft_strlen(arg + i));
	if (!content)
	{
		ms_perror("malloc", strerror(errno), NULL, NULL);
		return (NULL);
	}
	return (content);
}

int	new_variable(char *name, char *arg, t_ms *ms)
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
	free(content);
	return (SUCCESS);
}

int	get_operation(char *arg)
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
