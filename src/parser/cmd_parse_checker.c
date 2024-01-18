/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 23:41:31 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/23 23:41:31 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_syntax_error(char *str);

/*Esta función se encargará de comprobar que no existan erorres de sintaxis,
parejas de comillas incompletas... Entre otras cosas feas.

Si devuelve FAILURE quiere decir que ha habido
algún error de ese tipo en algún token.

Si se da el caso, esta función NO liberará nada. Lo único de lo que se encarga
esta función aparte de comprobar errores es de eliminar las comillas del anterior
string y de igualar este nuevo string alojado al puntero de content del token.
*/
int	check_tokens(t_ms *ms)
{
	t_token	*tmp;

	tmp = ms->token;
	while (tmp)
	{
		if (!check_token(tmp))
		{
			ms->exit_status = 258;
			return (FAILURE);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

/*	1. Se comprueba el token_type
	2. En función del token_type se comprueba si el siguiente es adecuado
	3. Si el token es de tipo texto se intentan eliminar las comillas.
	4. Se devuelve FALSE si algo falla*/
int	check_token(t_token *token)
{
	if (token->type == PIPE)
	{
		if (!token->next || token->next->type == PIPE || !token->prev)
			return (ms_syntax_error("|"));
	}
	else if (token->type != TEXT)
	{
		if (!token->next || token->next->type != TEXT)
		{
			if (!token->next)
				return (ms_syntax_error("newline"));
			else
				return (ms_syntax_error(token->next->content));
			return (FALSE);
		}
	}
	/* else
	{
		token->content = erase_brackets(token->content);
		if (!token->content)
			return (FALSE);
	} */
	return (TRUE);
}

int	is_empty(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!in_x(" \t", str[i]))
			return (FALSE);
	return (TRUE);
}

static int	ms_syntax_error(char *str)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, str, ft_strlen(str));
	write(2, "\'\n", 2);
	return (FALSE);
}