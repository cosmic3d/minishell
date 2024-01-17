/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:39:20 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/17 21:00:04 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	parse_flags(char **arg, int *index);

int	ms_echo(char **argv)
{
	// IMPORTANTISIMO!
	// Hay que comprobar si el echo de 42 puede interpretar flags aunque
	// vayan despues del contenido a printear
	// Ejemplo:
	// echo "Hola!" -n
	// En algunas versiones de bash esto es válido, hay que ver en 42
	int	n_flag;
	int	i;

	n_flag = 0;
	i = 1;
	if (argv[i])
	{
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
	return (SUCCESS);
}

static int	parse_flags(char **arg, int *index)
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
		if (arg[i][j] != '\0' || j == 0)
			break ;
		flag = 1;
		*index = i + 1;
	}
	return (flag);
}
