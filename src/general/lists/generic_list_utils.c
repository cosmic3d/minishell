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

/* Retorna la cantidad de nodos de una lista. */
int	list_len(void *head)
{
	t_lst	*temp;
	int		len;

	temp = (t_lst *)head;
	len = 0;
	while (temp)
	{
		temp = temp->next;
		len++;
	}
	return (len);
}
