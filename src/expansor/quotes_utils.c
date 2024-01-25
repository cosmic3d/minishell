/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:15:39 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/25 17:42:57 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Comprueba si el index recibido corresponde con uno de los valores
en el array recibido. Retorna 1 si lo encuentra y 0 si no.*/
int	is_valid_quote(int index, int *quote_array)
{
	int	i;

	i = 0;
	while (quote_array[i] != -1)
	{
		if (index == quote_array[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/* Gestiona los switches de las quotes y retorna TRUE si la quote en
str[index] es una quote activa, o FALSE si es una quote como caracter
literal */
int	is_active_quote(char *str, int index, t_quotes *q)
{
	if (index == 0)
	{
		q->d_on = OFF;
		q->s_on = OFF;
	}
	if (str[index] == '\'' && q->d_on == OFF && is_valid_quote(index, q->s))
	{
		q->s_on *= SWITCH;
		return (TRUE);
	}
	else if (str[index] == '"' && q->s_on == OFF && is_valid_quote(index, q->d))
	{
		q->d_on *= SWITCH;
		return (TRUE);
	}
	return (FALSE);
}
