/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:15:39 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/22 17:47:11 by apresas-         ###   ########.fr       */
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

// Maybe lo implemento para que el código sea más limpio
/* Gestiona el switching ON y OFF del *t_quotes recibido en base al
caracter en str[i] */
// void	quote_switch(char *str, int i, t_quotes *q)
// {
// 	if (str[i] == '\'' && q->d_on == OFF && is_valid_quote(i, q->s))
// 		q->s_on *= SWITCH;
// 	if (str[i] == '"' && q->s_on == OFF && is_valid_quote(i, q->d))
// 		q->d_on *= SWITCH;
// }

/* Gestiona los switches de las quotes y retorna TRUE si la quote en
str[index] es una quote activa, o FALSE si es una quote como caracter
literal */
int	is_active_quote(char *str, int index, t_quotes *q)
{
	if (index == 0) // Para reiniciar los estados de las quotes a OFF por si aca
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
