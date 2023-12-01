/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:37:51 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/29 11:58:11 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	exit_quit(int exit_status);
static int	argument_syntax(char *arg);
static long	exit_strtol(char *str, int *error);

int	ms_exit(char **argv)
{
	long	exit_status_l;
	int		exit_status;
	int		error;

	if (!argv[1])
		exit_quit(EXIT_SUCCESS);
	error = 0;
	exit_status_l = exit_strtol(argv[1], &error);
	if (argument_syntax(argv[1]) == FAILURE || error)
	{
		ms_perror("exit", NUMERIC_ARG, NULL, NULL);
		exit_status_l = 255;
	}
	if (argv[2])
	{
		ms_perror("exit", TOO_MANY_ARG, NULL, NULL);
		return (FAILURE);
	}
	exit_status = exit_status_l % 256;
	exit_quit(exit_status);
	return (0);
}

static void	exit_quit(int exit_status)
{
	write(STDOUT_FILENO, "exit\n", 5);
	restore_terminal_settings();
	rl_clear_history();
	exit(exit_status);
}

static long	exit_strtol(char *str, int *error)
{
	unsigned long	ul_num;
	long			num;
	int				i;

	i = 0;
	num = 1;
	ul_num = 0;
	while (ft_isspace(str[i]) == TRUE)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			num = -1;
		i++;
	}
	while (ft_isdigit(str[i]) == TRUE)
	{
		ul_num *= 10;
		ul_num += str[i] - '0';
		i++;
	}
	if ((ul_num > 9223372036854775807UL && num == 1) || \
		(ul_num > 9223372036854775808UL && num == -1))
		*error = 1;
	return (num * ul_num);
}

static int	argument_syntax(char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (ft_isdigit(arg[i]))
	{
		i++;
		len++;
	}
	if (len > 19)
		return (FAILURE);
	while (arg[i] == ' ' || arg[i] == '\t')
		i++;
	if (arg[i] != '\0')
		return (FAILURE);
	return (SUCCESS);
}
