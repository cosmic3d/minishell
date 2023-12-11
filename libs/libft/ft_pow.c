/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:43:35 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/11 14:53:13 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// STILL IN DEVELOPMENT, NOT READY
// Simplified function for exponentiation of long integers.
long	ft_pow(long base, long exp)
{
	long	result;
	long	abs_exp;
	int		i;

	result = 1;
	if (exp == 0)
		return (result);
	if (exp < 0)
		abs_exp = -exp;
	else
		abs_exp = exp;
	i = 0;
	while (i < abs_exp)
	{
		result *= base;
		i++;
	}
	if (exp < 0)
		result = 1 / result;
	return (result);
}

// STILL IN DEVELOPMENT, NOT READY
// Simplified function for exponentiation of long integers.
// Does not work for decimal exponents!
double	ft_powd(double base, double exponent)
{
	double	result;
	double	abs_exp;
	int		i;

	result = 1.0;
	if (exponent == 0)
		return (result);
	if (exponent < 0)
		abs_exp = -exponent;
	else
		abs_exp = exponent;
	i = 0;
	while (i < abs_exp)
	{
		result *= base;
		i++;
	}
	if (exponent < 0)
	{
		result = 1.0 / result;
	}
	return (result);
}
