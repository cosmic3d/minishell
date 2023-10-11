/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:04:11 by apresas-          #+#    #+#             */
/*   Updated: 2022/01/26 16:30:16 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	n_len;

	index = 0;
	n_len = ft_strlen(needle);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[index] && index < len)
	{
		if (haystack[index] == needle[0]
			&& n_len <= (len - index)
			&& ft_strncmp(&haystack[index], needle, n_len) == 0)
		{
			return ((char *)&haystack[index]);
		}
		index++;
	}
	return (NULL);
}
