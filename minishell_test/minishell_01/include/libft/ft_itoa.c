/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 16:13:36 by apresas-          #+#    #+#             */
/*   Updated: 2023/02/09 14:44:09 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int number)
{
	int		number_len;
	int		i;
	char	*result;

	if (number == -2147483648)
		return (ft_strdup("-2147483648"));
	number_len = ft_intlen(number);
	result = malloc(number_len + 1);
	if (!result)
		return (0);
	i = number_len - 1;
	result[number_len] = '\0';
	if (number < 0)
	{
		number *= -1;
		result[0] = '-';
	}
	while (number / 10 != 0)
	{
		result[i] = (number % 10) + 48;
		number = number / 10;
		i--;
	}
	result[i] = (number % 10) + 48;
	return (result);
}
