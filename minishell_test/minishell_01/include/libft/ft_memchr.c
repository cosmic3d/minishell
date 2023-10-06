/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:09:50 by apresas-          #+#    #+#             */
/*   Updated: 2022/01/26 17:02:56 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int	len;

	len = 0;
	while ((size_t)len < n)
	{
		if ((*(unsigned char *)(s + len)) == (unsigned char)c)
			return ((unsigned char *)s + len);
		len++;
	}
	return (0);
}
