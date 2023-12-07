/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:38:01 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/07 13:53:46 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// IN DEVELOPMENT
// float	ft_atof(char *str)
// {
// 	float	num;
// 	float	decimal;
// 	int		i;
// 	int		sign;
// 	int		exp;

// 	num = 0.0;
// 	decimal = 0.0;
// 	i = 0;
// 	sign = 1;
// 	exp = 0;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	while (ft_isspace(str[i]) == 1)
// 		i++;
// 	while (ft_isdigit(str[i]) == 1)
// 	{
// 		num = num * 10 + (str[i] - '0');
// 		i++;
// 	}
// 	if (str[i] == '.')
// 	{
// 		i++;
// 		while (ft_isdigit(str[i]) == 1)
// 		{
// 			decimal = decimal * 10 + (str[i] - '0');
// 			exp--;
// 			i++;
// 		}
// 	}
// 	num = sign * (num + decimal * ft_pow(10, exp));
// 	return (num);
// }
