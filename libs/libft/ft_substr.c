/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:16:33 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/11 17:56:14 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	i = 0;
	if (len > s_len)
		len = s_len + 1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (start < s_len)
		while (i < len)
			str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
