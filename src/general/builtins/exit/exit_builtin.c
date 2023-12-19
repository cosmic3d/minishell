/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:37:51 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/19 18:24:35 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	exit_quit(int exit_status);

int	ms_exit(char **argv)
{
	long		arg_long;
	int			exit_status;

	// write(STDERR, "exit\n", 5);
	if (!argv[1])
		exit_quit(EXIT_SUCCESS);
	if (ft_islong(argv[1]) == FALSE)
	{
		ms_perror("exit", argv[1], NUMERIC_ARG, NULL);
		exit_status = 255;
	}
	else
	{
		arg_long = ft_strtol(argv[1]);
		exit_status = arg_long % 256;
	}
	if (argv[2])
	{
		ms_perror("exit", TOO_MANY_ARG, NULL, NULL);
		return (1);
	}
	exit_quit(exit_status);
	return (0);
}

// duda, habrá que cerrar file descriptors aquí también? Creo que si. //////////////////s
static void	exit_quit(int exit_status)
{
	restore_terminal_settings();
	rl_clear_history();
	exit(exit_status);
}
