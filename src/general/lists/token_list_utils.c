/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:45:34 by jenavarr          #+#    #+#             */
/*   Updated: 2024/01/22 15:44:39 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Obtiene el último token de una lista de tokens
t_token	*token_tail(t_token *token)
{
	if (!token)
		return (NULL);
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
	new->quotes = NULL;
	new->content = NULL;
	new->type = TEXT;
	new->hascontent = FALSE; // cambio Albert
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
		*token = (*token)->next;
		free_token(tmp);
	}
	*token = NULL;
	token = NULL;
}

void	free_token(t_token *tmp)
{
	tmp->prev = NULL;
	if (tmp->content)
		free(tmp->content);
	if (tmp->type == TEXT && tmp->quotes)
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
