/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:05:26 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/21 02:29:14 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Esta función devuelve el número de tokens que habrá que tokenizar */
static int	token_count(t_token *t, int count)
{
	int		i;
	char	bracks;

	i = -1;
	//printf("Content: %s\n", t->content);
	while (t->content[++i])
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
			if (t->content[i + 1])
				continue ;
		}
		count++;
		/* printf("Char %i is: %c\n", i, t->content[i]);
		printf("Count: %i\n", count); */
		while (t->content[i + 1] && t->content[i + 2] && t->content[i] == ' ')
			i++;
	}
	return (count);
}

/* Esta función devuelve unos strings de los tokens
que deberán de ser tokenizados.
Si devuelve NULL, quiere decir que únicamente
había un token, y que por lo tanto
no hace falta crear nuevos tokens ni nada.*/
static char	**token_splitter(t_token *token)
{
	int		num_tokens;
	char	**tk_contents;

	if (!ft_strlen(token->content))
		return (NULL);
	num_tokens = token_count(token, 0);
	printf("NUM OF TOKENS: %i\n", num_tokens);
	if (num_tokens == 1)
		return (NULL);
	tk_contents = (char **)malloc(sizeof(char *) * (num_tokens + 1));
	if (!tk_contents)
		ms_quit(MALLOC_ERR);

	return (tk_contents);
}

/* Esta función tokeniza un token, en el caso de que sea necesario.

Divide el contenido del token según los espacios y suprime las comillas
de los bordes y las vacías.

Para distinguir las comillas que escribió el usuario de las que se encuentran
al expandir utilizaré un array de enteros que contiene las posiciones de las
comillas que hay que tener en cuenta. */
t_token	*retokenizer(t_token *token)
{
	if (!token_splitter(token))
		return (token);
	return (token);
}
