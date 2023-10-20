/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:57:02 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/20 18:09:22 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_unset(t_ms *ms, char **argv)
{
	// estoy en ello
	if (!argv[1])
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
}
