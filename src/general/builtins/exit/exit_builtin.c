/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:37:51 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/23 18:44:24 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_long(char *str);
static void	exit_quit(int exit_status);

// VERSION B, HABRÁ QUE VER EN 42 CUAL MANDA
int	ms_exit(char **argv, int exit_status)
{
	exit_status %= 256;
	if (!argv[1])
		exit_quit(exit_status);
	exit_status = ft_strtol(argv[1]) % 256;
	if (is_long(argv[1]) == FALSE || !argv[1][0])
	{
		ms_perror("exit", argv[1], NUMERIC_ARG, NULL);
		exit_status = 255;
	}
	else if (argv[2])
	{
		ms_perror("exit", TOO_MANY_ARG, NULL, NULL);
		return (1);
	}
	exit_quit(exit_status);
	return (0);
}

// Adaptado para --
/* int	ms_exit(char **argv, int exit_status)
{
	int	i;

	i = 1;
	if (!ft_strcmp(argv[1], "--"))
		i = 2;
	exit_status %= 256;
	if (!argv[i])
		exit_quit(exit_status);
	exit_status = ft_strtol(argv[i]) % 256;
	if (is_long(argv[i]) == FALSE || !argv[i][0])
	{
		ms_perror("exit", argv[i], NUMERIC_ARG, NULL);
		exit_status = 255;
	}
	else if (argv[i + 1])
	{
		ms_perror("exit", TOO_MANY_ARG, NULL, NULL);
		return (1);
	}
	exit_quit(exit_status);
	return (0);
} */

static int	is_long(char *str)
{
	int		i;
	long	num;
	int		sign;

	i = -1;
	num = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '\0')
		return (FALSE);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 0;
		str++;
	}
	while (ft_isdigit(str[++i]))
	{
		if (num > LMAX_10 || (num == LMAX_10 && (str[i] - '0') > 8 - sign))
			return (0);
		num = (num * 10) + str[i] - '0';
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
