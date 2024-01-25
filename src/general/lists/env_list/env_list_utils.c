/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:18:13 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/25 19:14:22 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Añade una variable de entorno nueva a la lista y le da los valores name y
// content recibidos
int	env_add(char *name, char *content, t_env **head)
{
	t_env	*new;

	if (!name)
		return (FAILURE);
	new = env_new(head);
	if (!new)
		return (FAILURE);
	new->name = ft_strdup(name);
	if (!new->name)
		ms_quit(MALLOC_ERR);
	if (env_edit(new, content) == FAILURE)
	{
		env_remove(new);
		return (FAILURE);
	}
	return (SUCCESS);
}

// Inicializa un nodo nuevo en la lista de variables de entorno y devuelve su
// puntero o NULL si falla.
t_env	*env_new(t_env **head)
{
	t_env	*new;
	t_env	*last;

	new = malloc(sizeof(t_env));
	if (!new)
		ms_quit(MALLOC_ERR);
	new->prev = NULL;
	new->next = NULL;
	new->name = NULL;
	new->content = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		last = tail(*head);
		last->next = new;
		new->prev = last;
	}
	return (new);
}

// Edita el contenido de la variable de entorno recibida
int	env_edit(t_env *var, char *content)
{
	if (!var)
		return (FAILURE);
	if (var->content)
		free(var->content);
	if (content)
	{
		var->content = ft_strdup(content);
		if (!var->content)
			ms_quit(MALLOC_ERR);
	}
	else
		var->content = NULL;
	return (SUCCESS);
}

// Elimina limpiamente una variable de entorno de la lista
void	env_remove(t_env *var)
{
	if (!var)
		return ;
	if (var->prev)
		var->prev->next = var->next;
	if (var->next)
		var->next->prev = var->prev;
	if (var->name)
		free(var->name);
	if (var->content)
		free(var->content);
	free(var);
	return ;
}

// Elimina por completo la lista de variables de entorno
void	env_free(t_ms *ms)
{
	t_env	*current;
	t_env	*next;

	if (!ms->env)
		return ;
	current = ms->env;
	while (current)
	{
		next = current->next;
		env_remove(current);
		current = next;
	}
	ms->env = NULL;
}
