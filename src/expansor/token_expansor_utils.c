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
void	token_traverse(t_token *t, int *i)
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
		new_tkn->next = NULL;
		//printf("TOken content: %s\n", new_tkn->content);
	}
	free(strs);
	return (first_tkn);
}

/* Esta función auxiliar resta las comillas válidas al string que
se va a extraer y devuelve el string con el len adecuado. */
static int	ms_substr_helper(char *s, int start, int len, t_token *t)
{
	int	final_len;
	int	i;

	final_len = len;
	i = start;
	t->quotes->s_on = OFF; // cosas test
	t->quotes->d_on = OFF; // cosas test
	//printf("Initial len: %d\n", final_len);
	while (s[i] && i < start + len)
	{

		// Testeando cosas
		if (s[i] == '\'' && t->quotes->d_on == OFF \
		&& is_valid_quote(i, t->quotes->s))
		{
			final_len--;
			t->quotes->s_on *= SWITCH;
		}
		if (s[i] == '"' && t->quotes->s_on == OFF \
		&& is_valid_quote(i, t->quotes->d))
		{
			final_len--;
			t->quotes->d_on *= SWITCH;
		}



		// Como estaba antes, creo
		/* if ((s[i] == '"' || s[i] == '\'') && \
		is_valid_quote(i, goodbrack(s[i], t)))
			final_len--; */

		i++;
	}
	//printf("Final len: %d\n", final_len);
	return (final_len);
}

/* Este split es un split modificado de tal manera que se adapte a nuestras
necesidades con las comillas válidas. Además de hacer un split normal,
este también elimina las comillas válidas en base a los punteros de
las comillas contenido en el token.*/
char	*ms_substr(char *s, int start, int n, t_token *t)
{
	char	*str;
	int		s_len;
	int		i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	if (n > s_len)
		n = s_len + 1;
	n = ms_substr_helper(s, start, n, t);
	str = malloc(sizeof(char) * (n + 1));
	if (!str)
		ms_quit(MALLOC_ERR);
	t->quotes->s_on = OFF; // cosas test
	t->quotes->d_on = OFF; // cosas test
	while (i < n)
	{
		//printf("i: %d\n", i);
		if (s[start] == '\'' && t->quotes->d_on == OFF \
		&& is_valid_quote(start, t->quotes->s))
		{
			start++;
			t->quotes->s_on *= SWITCH;
		}
		else if (s[start] == '"' && t->quotes->s_on == OFF \
		&& is_valid_quote(start, t->quotes->d))
		{
			start++;
			t->quotes->d_on *= SWITCH;
		}
		else
			str[i++] = s[start++];
	}
	str[i] = '\0';
	return (str);
}
