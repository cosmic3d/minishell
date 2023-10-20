/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:29:58 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/17 16:48:54 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Compares two strings keeping in mind their lengths
int	ft_strlcmp(const char *s1, const char *s2)
{
	size_t	len;

	len = ft_low_strlen(s1, s2);
	return (ft_strncmp(s1, s2, len));
}
