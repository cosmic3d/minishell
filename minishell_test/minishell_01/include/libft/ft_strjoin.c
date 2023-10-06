/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:59:53 by apresas-          #+#    #+#             */
/*   Updated: 2022/02/01 13:35:14 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len;
	char	*str;

	len_s1 = ft_strlen(s1);
	len = ft_strlen(s2) + len_s1;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, len_s1 + 1);
	ft_strlcat(str, s2, len + 1);
	return (str);
}
