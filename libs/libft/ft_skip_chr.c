/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_chr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:05:07 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/09 14:23:56 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Receives a pointer to a char in a string, keeps track of the character at
that point in the string, then travels the string until that character is
found again. Returns the pointer to that string.
If the character is not found again, returns a NULL pointer. */
char	*ft_skip_chr_ptr(char *str)
{
	char	ch;

	ch = *str;
	str++;
	while (*str)
	{
		if (*str == ch)
			return (str);
		str++;
	}
	return (NULL);
}

/* Receives a string and an index, keeps track of the character at str[i]
then travels the string until that character is found again. Returns the 
new value of the index that was used to travel the string.
If the character is not found again, returns the index at which the
string ends. */
int	ft_skip_chr_i(char *str, int i)
{
	char	ch;

	ch = str[i];
	i++;
	while (str[i])
	{
		if (str[i] == ch)
			return (i);
		i++;
	}
	return (i);
}
