/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:27:13 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/10 18:43:43 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		env_get_content(char *env_line, t_env *env);

// Inicializa la lista de t_env llenando sus variables con el contenido de
// char **envp
// Si !envp, inicializa un solo nodo de la lista
t_env	*env_list(char **og_envp)
{
	t_env	*node;
	t_env	*head;
	t_env	*prev;
	int		i;

	i = 0;
	prev = NULL;
	if (!og_envp)
		return (env_new_node());
	while (og_envp[i])
	{
		node = env_new_node();
		if (!node)
			exit(EXIT_FAILURE);
		if (env_get_content(og_envp[i], node))
			exit(EXIT_FAILURE);
		env_add_node(&prev, node);
		if (i == 0)
			head = node;
		i++;
	}
	return (head);
}

t_env	*env_new_node(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		ms_error(MALLOC_ERR);
		return (NULL);
	}
	new->name = NULL;
	new->content = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static int	env_get_content(char *env_line, t_env *env)
{
	int	eq_i;

	eq_i = ft_strchr_i(env_line, '=');
	if (eq_i == -1)
	{
		// Esto hopefully no tiene que ocurrir nunca, pero dejo este error de momento
		printf("Error inesperado, ft_strchr_i en envp_dup.c\n");
		exit(1);
	}
	env->name = ft_substr(env_line, 0, eq_i);
	if (!env->name)
	{
		ms_error(MALLOC_ERR);
		return (1);
	}
	env->content = ft_substr(env_line, eq_i + 1, ft_strlen(env_line) - eq_i);
	if (!env->content)
	{
		ms_error(MALLOC_ERR);
		free(env->name);
		return (1);
	}
	return (0);
}

void	env_add_node(t_env **tail, t_env *new)
{
	if (*tail == NULL)
		*tail = new;
	else
	{
		new->prev = *tail;
		(*tail)->next = new;
		*tail = new;
	}
}

// OLD

// char	**ms_envp_dup(char **og_envp)
// {
// 	char	**envp;
// 	int		i;

// 	// Falta comprobar si envp no es NULL y todo eso
// 	envp = malloc(sizeof(char *) * ms_arraylen(og_envp) + 1);
// 	if (!envp)
// 		return (ms_error_ptr(MALLOC_ERR)); // malloc error
// 	i = 0;
// 	while (og_envp[i])
// 	{
// 		envp[i] = ft_strdup(og_envp[i]);
// 		if (!envp[i])
// 		{
// 			ms_error(MALLOC_ERR); // Lo he puesto aquí para indicar el error lo antes posible, pero podríamos hacerlo en el return
// 			while (i > 0)
// 			{
// 				i--;
// 				free(envp[i]);
// 			}
// 			return (NULL); // malloc error
// 		}
// 		i++;
// 	}
// 	envp[i] = NULL;
// 	return (envp);
// }
