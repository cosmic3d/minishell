/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:08:12 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/10 18:54:29 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_init(char **envp)
{
	t_env	*head;

	head = env_list(envp);
	if (!head)
		exit(EXIT_FAILURE);
	if (env_shlvl(head))
		exit(EXIT_FAILURE);
	return (head);
}

int	env_shlvl(t_env *head)
{
	t_env	*node;
	int		flag;

	node = head;
	flag = 0;
	if (node->next == NULL)
	{
		node->name = ft_strdup("SHLVL");
		node->content = ft_strdup("1");
	}
	while (node->next)
	{
		if (!ft_strcmp(node->name, "SHLVL"))
			return (env_update_shlvl(node));
		node = node->next;
	}
	node->next = env_new_node();
	if (!node->next)
		exit(1);
	env_add_node(&node, node->next);
	node->name = ft_strdup("SHLVL");
	node->content = ft_strdup("1");
	return (0);
}

int	env_update_shlvl(t_env *env)
{
	int	shlvl;

	shlvl = ft_atoi(env->content);
	free(env->content);
	if (shlvl + 1 >= 1000)
	{
		// Esto habrá que adaptarlo a nuestro formato de error si queremos ser pulcros
		printf(SHLVL_WARNING, shlvl + 1);
		env->content = ft_itoa(1);
		if (!env->content)
		{
			ms_error(MALLOC_ERR);
			return (1);
		}
		return (0);
	}
	env->content = ft_itoa(shlvl + 1);
	if (!env->content)
	{
		ms_error(MALLOC_ERR);
		return (1);
	}
	printf("%s=%s\n", env->name, env->content);
	return (0);
}
