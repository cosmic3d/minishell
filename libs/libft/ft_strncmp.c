/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:18:50 by apresas-          #+#    #+#             */
/*   Updated: 2022/01/20 13:09:00 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a1;
	unsigned char	*a2;

	a1 = (unsigned char *)s1;
	a2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (a1[i] != '\0' && a2[i] != '\0' && i < n - 1)
	{
		if (a1[i] > a2[i] || a1[i] < a2[i])
			return (a1[i] - a2[i]);
		else if (a1[i] == a2[i])
			i++;
	}
	if (a1[i] > a2[i] || a1[i] < a2[i])
		return (a1[i] - a2[i]);
	else
		return (0);
}
