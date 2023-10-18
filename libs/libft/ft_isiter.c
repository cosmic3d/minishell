/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:50:52 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/18 12:00:08 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* This function will iterate all characters in the string s and check them 
against one of the ft_isXXXXX functions like ft_isalnum, ft_isspace, etc. 
This function will return 1 if all the characters in the string s match the 
specified function.
It will return 0 if !s or if any character did not match the function. */
int	ft_isiter(const char *s, int (*f)(int))
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (!f(s[i]))
			return (0);
		i++;
	}
	return (1);
}
