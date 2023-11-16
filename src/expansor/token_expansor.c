/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:05:26 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/16 20:22:09 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Función auxiliar que devuelve  */
static int	*goodbrack(char bracks, t_token *t)
{
	if (bracks == '\"')
		return (t->quotes->d);
	return (t->quotes->s);
}

/* Esta función devuelve el número de tokens que habrá que tokenizar */
static int	token_count(t_token *t)
{
	int		i;
	int		count;
	char	bracks;

	i = -1;
	count = 1;
	printf("Content: %s\n", t->content);
	while (t->content[++i])
	{
		if (t->content[i] != ' ')
		{
			if (t->content[i] == '"' || t->content[i] == '\'')
			{
				bracks = t->content[i++];
				while (t->content[i] && !(t->content[i] == bracks && \
				is_valid_quote(i, goodbrack(bracks, t))))
					i++;
			}
			continue ;
		}
		while (t->content[i] && t->content[i] == ' ')
			i++;
		count++;
	}
	return (count);
}

/* Esta función devuelve unos strings de los tokens
que deberán de ser tokenizados. */
static char	**token_splitter(t_token *token)
{
	int	num_tokens;

	num_tokens = token_count(token);
	printf("NUM OF TOKENS: %i\n", num_tokens);
	if (num_tokens == 1)
		return (NULL);
	return (NULL); //ESTO NO ES ASÍ ES PARA UNA PRUEBA
}

/* Esta función tokeniza un token, en el caso de que sea necesario.

Divide el contenido del token según los espacios y suprime las comillas
de los bordes y las vacías.

Para distinguir las comillas que escribió el usuario de las que se encuentran
al expandir utilizaré un array de enteros que contiene las posiciones de las
comillas que hay que tener en cuenta. */
t_token	*retokenizer(t_token *token)
{
	token_splitter(token);
	return (token);
}
