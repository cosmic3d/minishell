/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:57:12 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/22 16:45:52 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_env_var_parts(char *name, char *content);

/* Convierte la lista de variables de entorno en un char **envp para enviarlo
como argumento a un programa. */
char	**env_list_to_envp(t_env *head)
{
	char	**envp;
	int		len;
	int		i;

	len = list_len(head);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		ms_quit(MALLOC_ERR);
	envp[len] = NULL;
	i = 0;
	while (head)
	{
		envp[i] = join_env_var_parts(head->name, head->content);
		head = head->next;
		i++;
	}
	return (envp);
}

static char	*join_env_var_parts(char *name, char *content)
{
	char	*joined;
	char	*aux;

	aux = ft_strjoin(name, "=");
	if (!aux)
		ms_quit(MALLOC_ERR);
	if (!content)
		return (aux);
	joined = ft_strjoin(aux, content);
	if (!joined)
		ms_quit(MALLOC_ERR);
	free(aux);
	return (joined);
}
