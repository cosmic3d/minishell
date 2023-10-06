/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:07:58 by apresas-          #+#    #+#             */
/*   Updated: 2023/02/11 19:43:21 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *str, int chr)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr_fd("Error\nThis should be a SEGMENTATION FAULT\n", 2);
		ft_putstr_fd("A NULL pointer has been sent to ft_strchr\n", 2);
		return (NULL);
	}
	while (chr > 127)
		chr -= 128;
	while (str[i] != '\0')
	{
		if (str[i] == (char)chr)
			return (str + i);
		i++;
	}
	if (chr == '\0')
		return (str + i);
	return (NULL);
}
