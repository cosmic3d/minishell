/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:35:31 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/13 20:40:13 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Funciones de lista genéricas en este archivo: */

/* Retorna el último elemento de cualquier lista */
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
	while (list->prev)
	{
		list = list->prev;
	}
	return (list);
}

// /* Crea un nuevo nodo en una lista generica */
// int	append(t_lst **head, size_t size)
// {
// 	t_lst	*new;
// 	t_lst	*last;

// 	write(1, "HOLIS2\n", 8);
// 	new = malloc(size);
// 	if (!new)
// 	{
// 		ms_error(MALLOC_ERR);
// 		return (FAILURE);
// 	}
// 	write(1, "HOLIS\n", 7);
// 	new->prev = NULL;
// 	new->next = NULL;
// 	if (*head == NULL)
// 		*head = new;
// 	else
// 	{
// 		write(1, "HOLIS3\n", 8);
// 		last = tail(*head);
// 		write(1, "HOLIS4\n", 8);
// 		last->next = new;
// 		new->prev = last;
// 	}
// 	return (SUCCESS);
// }
