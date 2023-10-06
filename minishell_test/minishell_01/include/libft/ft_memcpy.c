/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:09:46 by apresas-          #+#    #+#             */
/*   Updated: 2022/01/31 13:30:13 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	n_aux;

	n_aux = 0;
	if (!dst && !src)
		return (0);
	while (n_aux < n)
	{
		((unsigned char *)dst)[n_aux] = ((unsigned char *)src)[n_aux];
		n_aux++;
	}
	return (dst);
}
