/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:35:31 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/20 18:39:29 by apresas-         ###   ########.fr       */
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

/* Crea un nuevo nodo en una lista generica */
int	append(t_lst **head, size_t size)
{
	t_lst	*new;
	t_lst	*last;

	new = malloc(size);
	if (!new)
	{
		ms_error(MALLOC_ERR);
		return (FAILURE);
	}
	new->prev = NULL;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		last = tail(*head);
		last->next = new;
		new->prev = last;
	}
	return (SUCCESS);
}

// Swapea dos elementos de una lista
void	swap(void *ptr_a, void *ptr_b)
{
	t_lst	*a;
	t_lst	*b;
	t_lst	*temp;

	if (!ptr_a | !ptr_b)
		return ;
	a = (t_lst *)ptr_a;
	b = (t_lst *)ptr_b;
	if (a->prev)
		a->prev->next = b;
	if (b->prev)
		b->prev->next = a;
	if (a->next != b)
	{
		temp = a->next;
		a->next = b->next;
		b->next = temp;
	}
	else
		b->next = a;
	return ;
}


// Version e chus
/* Crea un nuevo nodo en una lista generica */
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
