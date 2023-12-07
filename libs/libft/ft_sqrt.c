/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:16:05 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/07 12:39:25 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_sqrt(double x)
{
	double	result;
	double	guess;

	if (x == 0.0 || x == 1.0)
		return (x);
	result = x / 2.0;
	while (1)
	{
		guess = 0.5 * (result + x / result);
		if (guess == result)
			break ;
		result = guess;
	}
	return (result);
}

double	ft_rsqrt(double x)
{
	return (1.0 / ft_sqrt(x));
}
