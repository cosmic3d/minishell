/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:35:31 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/13 18:29:55 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Funciones de lista genéricas en este archivo: */

// /* Retorna el último elemento de cualquier lista */
void	*tail(void *node)
{
	t_lst	*list;

	list = (t_lst *)node;
	while (list->next != NULL)
	{
		list = list->next;
	}
	return (list);
}

/* Retorna el primer elemento de cualquier lista */
void	*head(void *node)
{
	t_lst	*list;

	list = (t_lst *)node;
	check();
	while (list->prev)
	{
		check();
		list = list->prev;
	}
	check();
	return (list);
}
