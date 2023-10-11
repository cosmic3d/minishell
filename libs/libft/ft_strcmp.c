/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:23:33 by apresas-          #+#    #+#             */
/*   Updated: 2023/02/08 13:26:05 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*a1;
	unsigned char	*a2;

	a1 = (unsigned char *)s1;
	a2 = (unsigned char *)s2;
	i = 0;
	while (a1[i] != '\0' && a2[i] != '\0')
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
