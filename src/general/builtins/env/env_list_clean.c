/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:33:11 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/28 16:41:11 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// idk man

// void	clean_env(t_env *env)
// {
// 	int		i;
// 	t_env	*aux;

// 	i = 0;
// 	while (env)
// 	{
// 		if (env->name)
// 			free(env->name);
// 		if (env->content)
// 			free(env->content);
// 		// if (env->prev) // idk
// 			// free(env->prev);
// 		if (env->next)
// 		{
// 			aux = env;
// 			env = env->next;
// 			free(aux);
// 		}
// 	}
// 	free(env); // creo
// }