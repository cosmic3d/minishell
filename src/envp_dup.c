/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:27:13 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/10 14:44:41 by apresas-         ###   ########.fr       */
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


// t_env	*ms_get_envp(char **og_envp)
// {
// 	t_env	*head;
// 	int		i;

// 	i = 0;
// 	while (og_envp[i])
// 	{

// 	}
// }

t_env	*new_env_in_list(char *env_line)
{
	t_env	*new;
	int		eq_i;

	eq_i = ft_strchr_i(env_line, '=');
	new->name = ft_substr(env_line, 0, eq_i);
	if (!new->name)
		return (NULL); // malloc error
	new->content = ft_substr(env_line, eq_i + 1, ft_strlen(env_line) - eq_i);
	if (!new->content)
		return (NULL); // malloc error
}

int	get_env_content(char *env_line, t_env *env)
{
	int	eq_i;

	eq_i = ft_strchr_i(env_line, '=');
	env->name = ft_substr(env_line, 0, eq_i);
	if (!env->name)
	{
		//print malloc error
		return (1);
	}
	env->content = ft_substr(env_line, eq_i + 1, ft_strlen(env_line) - eq_i);
	if (!env->content)
	{
		// print malloc error
		free(env->name);
		return (1);
	}
	return (0);
}
