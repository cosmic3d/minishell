/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:11:36 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/29 12:05:36 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/* función que emula el builtin env */
int	ms_env(t_ms *ms)
{
	t_env	*var;

	var = ms->env;
	while (var)
	{
		if (var->name && var->content)
		{
			write(STDOUT_FILENO, var->name, ft_strlen(var->name));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, var->content, ft_strlen(var->content));
			write(STDOUT_FILENO, "\n", 1);
		}
		var = var->next;
	}
	return (SUCCESS);
}
