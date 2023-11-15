/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:29:59 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/20 18:10:43 by apresas-         ###   ########.fr       */
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

/* Retorna el puntero al nodo de la lista de variables de entorno cuyo nombre 
es name. Si no lo encuentra, devuelve NULL */
t_env	*env_find(char *name, t_env *head)
{
	while (head)
	{
		if (!ft_strcmp(head->name, name))
		{
			return (head);
		}
		head = head->next;
	}
	return (NULL);
}

/* Elimina la variable de entorno de nombre name de la lista t_env de forma 
limpia. Si en la lista no hay variable de entorno con este nombre, retorna 1. */
int	env_remove(char *name, t_env *env)
{
	t_env	*remove;

	remove = env_find(name, env);
	if (!remove)
		return (FAILURE);
	if (remove->prev)
		remove->prev->next = remove->next;
	if (remove->next)
		remove->next->prev = remove->prev;
	free(remove->name);
	free(remove->content);
	free(remove);
	return (SUCCESS);
}

/* Busca la variable de entorno en base a su ->name y actualiza su ->content.
Si la variable no existe, retorna 1. Si ft_strdup falla, termina el programa. */
int	env_update(char *name, char *content, t_env *env)
{
	t_env	*change;

	change = env_find(name, env);
	if (!change)
		return (FAILURE);
	free(change->content);
	change->content = ft_strdup(content);
	if (!change->content)
		ms_quit(MALLOC_ERR);
	return (SUCCESS);
}

/* Obtiene el contenido de una variable de entorno de nombre name.
Si la variable no existe, retorna el contenido ""
Retorna un puntero nuevo, de esta forma no hay riesgo de sobreescribir el 
contenido de la variable accidentalmente. */
char	*get_env_content(char *name, t_env *env)
{
	t_env	*variable;
	char	*content;

	variable = env_find(name, env);
	if (!variable)
	{
		content = ft_strdup("");
		if (!content)
			ms_quit(MALLOC_ERR);
		return (content);
	}
	content = ft_strdup(variable->content);
	if (!content)
		ms_quit(MALLOC_ERR);
	return (content);
}
