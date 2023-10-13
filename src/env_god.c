/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_god.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:29:59 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/13 17:58:20 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Añade una nueva variable de entorno a la lista t_env */
int	env_add(char *name, char *content, t_env **head)
{
	t_env	*new;
	t_env	*last;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		ms_error(MALLOC_ERR);
		return (FAILURE);
	}
	new->prev = NULL;
	new->next = NULL;
	new->name = NULL;
	new->content = NULL;
	if (env_add_content(name, content, new))
		return (FAILURE);
	if (*head == NULL)
		*head = new;
	else
	{
		last = tail(*head);
		last->next = new;
		new->prev = last;
	}
	return (SUCCESS);
}

/* Añade los valores para ->name y ->content en un elemento de la lista de 
variables de entorno. */
int	env_add_content(char *name, char *content, t_env *new)
{
	if (name)
	{
		new->name = ft_strdup(name);
		if (!new->name)
		{
			ms_error(MALLOC_ERR);
			free(new);
			return (FAILURE);
		}
	}
	if (content)
	{
		new->content = ft_strdup(content);
		if (!new->content)
		{
			ms_error(MALLOC_ERR);
			free(new->name);
			free(new);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
