/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:08:29 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/07 17:19:45 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Retorna el puntero al nodo de la lista de variables de entorno cuyo nombre 
es name. Si no lo encuentra, devuelve NULL */
t_env	*env_find(char *name, t_env *head)
{
	if (!name)
		return (NULL);
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
