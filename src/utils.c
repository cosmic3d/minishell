/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:29:35 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/09 15:31:14 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Función análoga a strlen, pero con char** en vez de char*
Devuelve la len de un char **array, asumiendo que este termina con un NULL */
int	ms_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		i++;
	}
	return (i);
}
