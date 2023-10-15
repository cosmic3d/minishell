/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:45:34 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/15 17:22:29 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Obtiene el último token de una lista de tokens
t_token	*token_tail(t_token *token)
{
	while (token->next != NULL)
		token = token->next;
	return (token);
}

/* Añade un token a la linked list (la función genérica me da problemas creo) */
int	token_append(t_token **token)
{
	t_token	*new;
	t_token	*last;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
	{
		ms_error(MALLOC_ERR);
		return (FAILURE);
	}
	new->prev = NULL;
	new->next = NULL;
	if (*token == NULL)
		*token = new;
	else
	{
		last = token_tail(*token);
		last->next = new;
		new->prev = last;
	}
	return (SUCCESS);
}

//Libera todos los tokens y todos sus strings alojados
void	free_tokens(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = *token;
		tmp->prev = NULL;
		*token = (*token)->next;
		free(tmp->content);
		free(tmp);
		tmp = NULL;
	}
	*token = NULL;
	token = NULL;
}
