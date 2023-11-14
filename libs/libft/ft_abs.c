/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:14:41 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/14 16:15:48 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the absolut value of the received integer. */
int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}
