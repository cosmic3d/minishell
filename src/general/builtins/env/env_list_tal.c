/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_tal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:53:48 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/29 16:36:51 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Añade una variable de entorno a la lista t_env
name y content siempre serán copiados, no se utilizará el puntero recibido.
Un name es obligatorio, content puede ser NULL. */
int	env_add(char *name, char *content, t_env **head)
{
	t_env	*new;

	if (!name)
		return (FAILURE); // veremos
	new = env_new(head); // nombre pendiente
	if (!new)
		return (FAILURE);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		ms_perror("malloc", strerror(errno), NULL, NULL);
		env_remove2(new);
		return (FAILURE);
	}
	if (env_edit(new, content) == FAILURE)
	{
		env_remove2(new);
		return (FAILURE);
	}
	return (SUCCESS);
}

/* Esto inicializa un puntero t_env */
t_env	*env_init(t_env **head)
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

/* Edita el content de una variable de entorno */
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
		{
			ms_perror("malloc", strerror(errno), NULL, NULL);
			return (FAILURE);
		}
	}
	else
		var->content = NULL;
	return (SUCCESS);
}

void	env_remove2(t_env *remove)
{
	if (!remove)
		return ;
	if (remove->prev)
		remove->prev->next = remove->next;
	if (remove->next)
		remove->next->prev = remove->prev;
	if (remove->name)
		free(remove->name);
	if (remove->content)
		free(remove->content);
	free(remove);
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
		env_remove2(current);
		current = next;
	}
}

//////

int	check_envp_syntax(char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			// Primer caracter alpha o '_'
			// Hasta encontrar '=', caracteres alnum o '_'
		}
	}
	return (SUCCESS);
}