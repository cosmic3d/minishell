/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:37:51 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/16 18:55:09 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_long(char *str);
static void	exit_quit(int exit_status);

// VERSION B, HABRÁ QUE VER EN 42 CUAL MANDA
int	ms_exit(char **argv, int exit_status)
{
	long		arg_long;
	int			err;

	err = 0;
	if (!argv[1])
		exit_quit(exit_status);
	if (is_long(argv[1]) == FALSE)
	{
		ms_perror("exit", argv[1], NUMERIC_ARG, NULL);
		// exit_status = 255; // así es en 42
		exit_status = 2; // bash 5.1.4(1) // testing en casa
		err = 1;
	}
	else
	{
		arg_long = ft_strtol(argv[1]);
		exit_status = arg_long % 256;
	}
	if (argv[2] && !err)
	{
		ms_perror("exit", TOO_MANY_ARG, NULL, NULL);
		return (1);
	}
	exit_quit(exit_status);
	return (0);
}

// OG:
// int	ms_exit(char **argv)
// {
// 	long		arg_long;
// 	int			exit_status;
// 	int			err;

// 	err = 0;
// 	if (!argv[1])
// 		exit_quit(EXIT_SUCCESS);
// 	if (is_long(argv[1]) == FALSE)
// 	{
// 		ms_perror("exit", argv[1], NUMERIC_ARG, NULL);
// 		// exit_status = 255; // así es en 42
// 		exit_status = 2; // bash 5.1.4(1) // testing en casa
// 		err = 1;
// 	}
// 	else
// 	{
// 		arg_long = ft_strtol(argv[1]);
// 		exit_status = arg_long % 256;
// 	}
// 	if (argv[2] && !err)
// 	{
// 		ms_perror("exit", TOO_MANY_ARG, NULL, NULL);
// 		return (1);
// 	}
// 	exit_quit(exit_status);
// 	return (0);
// }
// NOTAS:
// EN CASA, AL MENOS, EXIT RETORNA COMO DEFAULT EL EXIT_STATUS ACTUAL
// HABRÁ QUE VER CÓMO LO HACE BASH EN 42!

static int	is_long(char *str)
{
	int		i;
	long	num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 0;
		str++;
	}
	while (ft_isdigit(str[i]))
	{
		if (num > LMAX_10 || (num == LMAX_10 && (str[i] - '0') > 8 - sign))
			return (0);
		num = (num * 10) + str[i] - '0';
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	return ((i > 0) && (str[i] == '\0'));
}

static void	exit_quit(int exit_status)
{
	restore_terminal_settings();
	rl_clear_history();
	exit(exit_status);
}
