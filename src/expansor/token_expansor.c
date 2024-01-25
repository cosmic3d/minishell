/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:05:26 by jenavarr          #+#    #+#             */
/*   Updated: 2024/01/25 18:02:47 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_count(t_token *t, int count, int i)
{
	char	bracks;

	while (t->content[i])
	{
		if (t->content[i + 1] && t->content[i] != ' ')
		{
			if ((t->content[i] == '"' || t->content[i] == '\'') && \
			is_valid_quote(i, goodbrack(t->content[i], t)))
			{
				bracks = t->content[i++];
				while (t->content[i + 1] && !(t->content[i] == bracks && \
				is_valid_quote(i, goodbrack(bracks, t))))
					i++;
			}
			if (t->content[i + 1] && ++i != -1)
				continue ;
		}
		if (++count != -1 && t->content[i] != ' ')
			i++;
		else
			while (t->content[i] == ' ')
				i++;
	}
	return (count);
}

/* Itera todo el string de un token y va haciendo substrings de los tokens
nuevos que vaya encontrando para añadirlos a strs y luego devolverlo*/
static char	**token_splitter_helper(char **strs, t_token *t, int tkn_count)
{
	int		i;
	int		start;
	int		str_i;

	i = 0;
	str_i = 0;
	while (t->content[i] && str_i < tkn_count)
	{
		if (t->content[i] && t->content[i] != ' ')
		{
			start = i;
			token_traverse(t, &i);
			strs[str_i] = ms_substr(t->content, start, i - start, t);
			if (!strs[str_i])
				ms_quit(MALLOC_ERR);
			str_i++;
		}
		if (t->content[i])
			i++;
	}
	strs[str_i] = NULL;
	return (strs);
}

/* Une los tokens nuevos en un solo token y devuelve el token nuevo */
static t_token	*token_splitter(t_token *token)
{
	int		num_tokens;
	char	**tk_contents;
	t_token	*new_tkn;

	if (!ft_strlen(token->content))
		return (NULL);
	num_tokens = token_count(token, 0, 0);
	if (num_tokens == 1)
		return (NULL);
	tk_contents = (char **)malloc(sizeof(char *) * (num_tokens + 1));
	if (!tk_contents)
		ms_quit(MALLOC_ERR);
	tk_contents = token_splitter_helper(tk_contents, token, num_tokens);
	new_tkn = token_joiner(tk_contents);
	return (new_tkn);
}

/* Esta función tokeniza un token, en el caso de que sea necesario.

Divide el contenido del token según los espacios y suprime las comillas
de los bordes y las vacías.

Para distinguir las comillas que escribió el usuario de las que se encuentran
al expandir utilizaré un array de enteros que contiene las posiciones de las
comillas que hay que tener en cuenta. */
t_token	*retokenizer(t_token *token, t_ms *ms, t_token	*nt, char *tmp)
{
	nt = token_splitter(token);
	if (!nt)
	{
		tmp = token->content;
		token->content = ms_substr(token->content, 0, \
		ft_strlen(token->content), token);
		free(tmp);
		return (token);
	}
	if (token->prev)
	{
		token->prev->next = nt;
		nt->prev = token->prev;
	}
	else
		ms->token = nt;
	if (token->next)
	{
		token->next->prev = nt;
		check_for_token_content(nt);
		nt = token_tail(ms->token);
		nt->next = token->next;
		return (free_token(token), nt);
	}
	return (free_token(token), token_tail(ms->token));
}

void	check_for_token_content(t_token *token)
{
	int	i;

	i = 0;
	token->hascontent = FALSE;
	while (token->content[i])
	{
		if (token->content[i] != ' ')
			token->hascontent = TRUE;
		i++;
	}
	return ;
}
