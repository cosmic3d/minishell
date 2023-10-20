/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:11:36 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/20 18:08:54 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TO-DO:
*/

/* Printea el output del BUILTIN 'env' */
int	ms_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->content && !ft_strlcmp(current->name, "?"))
			printf("%s=%s\n", current->name, current->content);
		current = current->next;
	}
	return (SUCCESS);
}
