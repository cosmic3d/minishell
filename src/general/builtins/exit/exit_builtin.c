/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:37:51 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/27 18:50:42 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exit(char **argv)
{
	int	exit_status;

	if (!argv[1])
		exit(EXIT_SUCCESS);
	if (argv[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (FAILURE);
	}
	exit_status = ft_atoi(argv[1]);
}
