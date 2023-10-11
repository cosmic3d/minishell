/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:05:32 by apresas-          #+#    #+#             */
/*   Updated: 2022/01/27 14:07:01 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (!src && !dst)
		return (0);
	if (src >= dst)
		i = 0;
	else if (src < dst)
		i = len;
	while (len != 0)
	{
		if (src >= dst)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
		else if (src < dst)
		{
			i--;
			((char *)dst)[i] = ((char *)src)[i];
		}
		len--;
	}
	return (dst);
}
