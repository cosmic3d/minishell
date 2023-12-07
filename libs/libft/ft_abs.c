/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:14:41 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/07 13:17:23 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns the absolute value of the integer recieved
int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

// Returns the absolute value of the long integer recieved
long	ft_absl(long num)
{
	if (num < 0)
		return (-num);
	return (num);
}

// Returns the absolute value of the float recieved
float	ft_absf(float num)
{
	if (num < 0.0)
		return (-num);
	return (num);
}

// Returns the absolute value of the double recieved
double	ft_absd(double num)
{
	if (num < 0.0)
		return (-num);
	return (num);
}
