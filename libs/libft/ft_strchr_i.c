/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:07:58 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/11 18:17:45 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_i(char *str, int chr)
{
	int	i;

	i = 0;
	while (chr > 127)
		chr -= 128;
	while (str[i] != '\0')
	{
		if (str[i] == (char)chr)
			return (i);
		i++;
	}
	if (chr == '\0')
		return (i);
	return (-1);
}
