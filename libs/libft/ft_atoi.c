/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:53:12 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/07 12:00:58 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	num = num * sign;
	return (num);
}

t_uint	ft_atou(char *str)
{
	int				i;
	unsigned int	num;

	i = 0;
	num = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) == 1)
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	return (num);
}
