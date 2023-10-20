/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_low_strlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:36:34 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/17 16:57:09 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the value of the lowest len of both strings using ft_strlen
If any of the two strings is NULL, a len of INT_MAX will be assumed and chances
are, the len of the other string will be returned.
If none of the strings exist, a len of 0 will be returned. */
size_t	ft_low_strlen(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;

	len1 = 2147483647;
	len2 = 2147483647;
	if (!s1 && !s2)
		return (0);
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	if (len1 < len2)
		return (len1);
	else
		return (len2);
}
