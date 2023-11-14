/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:41:04 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/14 12:44:35 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the amount of times the char c is found in the string pointed to by 
str. The value of the char c is not evaluated in any way. */
int	ft_chrcount(char *str, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
