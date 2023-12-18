/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:57:12 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/18 17:51:20 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Creo que está listo, pero falta revisarlo

/* Convierte la lista de variables de entorno en un char **envp para enviarlo
como argumento a un programa. */
char	**env_list_to_envp(t_env *head)
{
	char	**envp;
	char	*aux;
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
		aux = ft_strjoin(head->name, "=");
		if (!aux)
			ms_quit(MALLOC_ERR);
		// printf("name = %s\ncontent = %s\n",head->name, head->content);
		if (!head->content)
		{
			envp[i] = aux;
			head = head->next;
			i++;
			continue;
		}
		envp[i] = ft_strjoin(aux, head->content);
		if (!envp[i])
			ms_quit(MALLOC_ERR); // mejorar?
		free(aux);
		head = head->next;
		i++;
	}
	return (envp);
}
