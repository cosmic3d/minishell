/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansor_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 00:45:38 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/21 00:45:38 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Función auxiliar que devuelve el puntero de comillas simples o dobles.
De esta manera se ahorran unas cuantas líneas. */
int	*goodbrack(char bracks, t_token *t)
{
	if (bracks == '\"')
		return (t->quotes->d);
	return (t->quotes->s);
}

/* Itera desde al principio hasta el final de un token con el puntero de i.
De esta manera tenemos más líneas para trabajar. */
static void	token_traverse(t_token *t, int *i)
{
	char	bracks;

	while (t->content[*i] && t->content[*i] != ' ')
	{
		if ((t->content[*i] == '"' || t->content[*i] == '\'') && \
		is_valid_quote(*i, goodbrack(t->content[*i], t)))
		{
			bracks = t->content[*i];
			*i = *i + 1;
			while (t->content[*i] && !(t->content[*i] == bracks && \
			is_valid_quote(*i, goodbrack(bracks, t))))
				*i = *i + 1;
		}
		*i = *i + 1;
	}
}

/* A partir de unos strings crea unos tokens y devuelve
el primero de ellos. También libera el strs. Si algo falla se sale*/
t_token	*token_joiner(char **strs)
{
	t_token	*first_tkn;
	t_token	*new_tkn;
	int		i;

	i = -1;
	new_tkn = NULL;
	while (strs[++i])
	{
		if (token_append(&new_tkn) == FAILURE)
			ms_quit(MALLOC_ERR);
		if (!i)
			first_tkn = new_tkn;
		new_tkn = token_tail(new_tkn);
		new_tkn->content = strs[i];
		new_tkn->type = TEXT;
		new_tkn->quotes = NULL;
		//printf("TOken content: %s\n", new_tkn->content);
	}
	free(strs);
	return (first_tkn);
}

/* Itera todo el string de un token y va haciendo substrings de los tokens
nuevos que vaya encontrando para añadirlos a strs y luego devolverlo*/
char	**token_splitter_helper(char **strs, t_token *t, int tkn_count)
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
			strs[str_i] = ft_substr(t->content, start, i - start + 1);
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
