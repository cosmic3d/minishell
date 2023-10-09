/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:27:13 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/09 18:48:07 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_envp_dup(char **og_envp)
{
	char	**envp;
	int		i;

	// Falta comprobar si envp no es NULL y todo eso
	envp = malloc(sizeof(char *) * ms_arraylen(og_envp) + 1);
	if (!envp)
		return (ms_error_ptr(MALLOC_ERR)); // malloc error
	i = 0;
	while (og_envp[i])
	{
		envp[i] = ft_strdup(og_envp[i]);
		if (!envp[i])
		{
			ms_error(MALLOC_ERR); // Lo he puesto aquí para indicar el error lo antes posible, pero podríamos hacerlo en el return
			while (i > 0)
			{
				i--;
				free(envp[i]);
			}
			return (NULL); // malloc error
		}
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
