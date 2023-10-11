/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:53:33 by apresas-          #+#    #+#             */
/*   Updated: 2023/02/09 13:57:41 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putaddress(unsigned long long address)
{
	ft_putstr("0x");
	if (!address)
		ft_putstr("0");
	else
		ft_puthex(address);
	return ;
}
