/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_list_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:58:39 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/04 17:00:05 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_add(char *name, char *content, t_env **head)
{
	t_env	*new;

	if (!name)
		return (FAILURE); // No sé si retornar failure, por que en realidad asegurarme de que una variable sin nombre no sea añadida es parte del funcionamiento esperable de esta función
	new = env_new(head);
	if (!new)
		return (FAILURE);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		ms_perror("malloc", strerror(errno), NULL, NULL);
		env_remove(new);
		return (FAILURE);
	}
	if (env_edit(new, content) == FAILURE)
	{
		env_remove(new);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_env	*env_new(t_env **head)
{
	t_env	*new;
	t_env	*last;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		ms_perror("malloc", strerror(errno), NULL, NULL);
		return (NULL);
	}
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

void	free_env_list(t_ms *ms)
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
}

int	update_env(t_env *var, char *content)
{
	if (!var)
		return (FAILURE);
	var->content = ft_strdup(content);
	if (!var->content)
		return (ms_perror("malloc", strerror(errno), NULL, NULL));
	return (SUCCESS);
}
