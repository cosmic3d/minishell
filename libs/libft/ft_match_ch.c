/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match_ch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:36:07 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/18 12:20:30 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Checks if the given character c is equal to any of the characters in the 
given pattern string 
Returns 1 if a match was found.
Returns 0 if no match was found. */
int	ft_match_ch(int c, const char *pattern)
{
	int	i;

	i = 0;
	while (pattern[i] != '\0')
	{
		if (c == pattern[i])
			return (1);
		i++;
	}
	return (0);
}
