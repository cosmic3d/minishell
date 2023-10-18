/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:17:48 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/18 12:21:23 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Checks if all the characters in the string str match with the pattern 
provided.
If all characters of str match the pattern, 1 is returned.
If str is NULL or if any of its characters doesn't match the pattern,
0 is returned. */
int	ft_match_str(char *str, const char *pattern)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_match_ch(str[i], pattern))
			return (0);
		i++;
	}
	return (1);
}
