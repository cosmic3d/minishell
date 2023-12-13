/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:11:36 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/13 12:31:26 by apresas-         ###   ########.fr       */
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
			write(STDOUT, var->name, ft_strlen(var->name));
			write(STDOUT, "=", 1);
			write(STDOUT, var->content, ft_strlen(var->content));
			write(STDOUT, "\n", 1);
		}
		var = var->next;
	}
	return (SUCCESS);
}
