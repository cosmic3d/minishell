/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:45:34 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/15 12:40:16 by apresas-         ###   ########.fr       */
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
		if (tmp->content)
			free(tmp->content);
		if (tmp->quotes) // Añadido por Albert -> Para liberar las quotes del token
		{
			if (tmp->quotes->d)
				free(tmp->quotes->d);
			if (tmp->quotes->s)
				free(tmp->quotes->s);
			free(tmp->quotes);
		}
		free(tmp);
		tmp = NULL;
	}
	*token = NULL;
	token = NULL;
}

//Devuelve true si almenos uno de los caracteres de str es c
int	in_x(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (TRUE);
	return (FALSE);
}
