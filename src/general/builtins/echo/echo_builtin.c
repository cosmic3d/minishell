/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:39:20 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/28 16:16:44 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_flags(char **arg, int *index);

int	ms_echo(char **argv)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	if (argv[1])
	{
		i = 1;
		n_flag = parse_flags(argv, &i);
		while (argv[i])
		{
			write(1, argv[i], ft_strlen(argv[i]));
			if (argv[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

int	parse_flags(char **arg, int *index)
{
	int	flag;
	int	i;
	int	j;

	i = *index - 1;
	flag = 0;
	while (arg[++i])
	{
		j = -1;
		while (arg[i][++j])
		{
			if (j == 0 && arg[i][j] != '-')
				break ;
			if (j != 0 && arg[i][j] != 'n')
				break ;
		}
		if (arg[i][j] != '\0')
			break ;
		flag = 1;
		*index = i + 1;
	}
	return (flag);
}
