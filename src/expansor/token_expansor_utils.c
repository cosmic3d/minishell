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

# include "minishell.h"

/* Función auxiliar que devuelve el puntero de comillas simples o dobles.
De esta manera se ahorran unas cuantas líneas. */
int	*goodbrack(char bracks, t_token *t)
{
	if (bracks == '\"')
		return (t->quotes->d);
	return (t->quotes->s);
}
