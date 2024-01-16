/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:13:35 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/16 18:21:45 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define ULONGMAX 18446744073709551615
#define ULMAX_10 1844674407370955161
#define LONGMAX 9223372036854775808
#define LMAX_10 922337203685477580
#define UINTMAX 4294967295
#define UIMAX_10 429496729
#define INTMAX 2147483647
#define IMAX_10 214748364

// Returns 1 if the str provided represents a valid integer, returns 0 otherwise
int	ft_isint(char *str)
{
	int		i;
	int		num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 0;
		str++;
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		if (IMAX_10 < num || (num == IMAX_10 && (str[i] - '0') > 8 - sign))
			return (0);
		num = (num * 10) + str[i] - '0';
		i++;
	}
	return (i > 0);
}

// Returns 1 if the str provided represents a valid unsigned integer, 
// returns 0 otherwise
int	ft_isuint(char *str)
{
	int				i;
	unsigned int	num;

	i = 0;
	num = 0;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '+')
		str++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		if (UIMAX_10 < num || (num == UIMAX_10 && (str[i] - '0') > 5))
			num = (num * 10) + str[i] - '0';
		i++;
	}
	return (i > 0);
}

// Returns 1 if the str provided represents a valid long integer, 
// returns 0 otherwise
int	ft_islong(char *str)
{
	int		i;
	long	num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 0;
		str++;
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		if (LMAX_10 < num || (num == LMAX_10 && (str[i] - '0') > 8 - sign))
			return (0);
		num = (num * 10) + str[i] - '0';
		i++;
	}
	return (i > 0);
}

// Returns 1 if the str provided represents a valid unsigned long integer, 
// returns 0 otherwise
int	ft_isulong(char *str)
{
	int				i;
	unsigned long	num;

	i = 0;
	num = 0;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '+')
		str++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		if (ULMAX_10 < num || (num == ULMAX_10 && (str[i] - '0') > 5))
			return (0);
		num = (num * 10) + str[i] - '0';
		i++;
	}
	return (i > 0);
}
