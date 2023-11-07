/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:57:02 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/07 17:25:49 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_verify_name(char *arg);

/* función que emula el builtin unset */
int	ms_unset(t_ms *ms, char **argv)
{
	int	i;

	i = 0;
	if (!argv[1])
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	while (argv[i])
	{
		if (unset_verify_name(argv[i]) == SUCCESS)
		{
			env_remove(argv[i], ms->env);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	unset_verify_name(char *arg)
{
	int		i;

	i = 0;
	if (ft_isdigit(arg[0]))
		return (FAILURE);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (FAILURE);
		i++;
	}
	if (i == 0)
		return (FAILURE);
	return (SUCCESS);
}
