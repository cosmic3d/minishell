/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:16:51 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/13 13:47:46 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_strtol(const char *str)
{
	long	number;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	number = 0;
	while (ft_isspace(str[i]) == 1)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		number = number * 10;
		number = number + str[i] - 48;
		i++;
	}
	number *= sign;
	return (number);
}

t_ulong	ft_strtoul(const char *str)
{
	t_ulong	number;
	int		i;

	number = 0;
	i = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) == 1)
	{
		number = number * 10;
		number = number + str[i] - '0';
		i++;
	}
	return (number);
}
