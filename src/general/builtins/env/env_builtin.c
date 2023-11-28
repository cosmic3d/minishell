/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:11:36 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/28 16:52:42 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* función que emula el builtin env */
int	ms_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->content)
			printf("%s=%s\n", current->name, current->content);
		current = current->next;
	}
	return (SUCCESS);
}
