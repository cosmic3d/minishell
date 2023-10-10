/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:37:05 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/10 18:24:09 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	env_update_shlvl(t_env *env);

// t_env	*env_shlvl(t_env *env)
// {
// 	t_env	*head;
// 	int		flag;

// 	flag = 0;
// 	head = env;
// 	while (env->next != NULL)
// 	{
// 		if (!ft_strcmp(current->name, "SHLVL"))
// 		{
// 			if (env_update_shlvl(current))
// 				exit(1);
// 			flag = 1;
// 		}
// 		current = current->next;
// 	}
// 	if (flag == 0)
// 	{
// 		current->next = env_new_node();
// 		if (!current->next)
// 			exit(1);
// 		env_add_node(&current, current->next);
// 	}
// 	return (head);
// }

