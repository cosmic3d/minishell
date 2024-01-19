/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:27:34 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/19 17:57:26 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_quote_struct(t_token *token);
static int	*get_quotes(char *str, char get);
static void	expand(t_ms *ms, t_token *token);

/* Itera por la lista de tokens de la linea de comandos actual y, si son de tipo
TEXT, los hace pasar por el proceso que expandirá sus variables de entorno y
retokenizará su contenido si es necesario. */
int	expansor(t_ms *ms, t_token *token)
{
	while (token)
	{
		// printf("Current token \"%s\"\n", token->content);
		if (token->type == TEXT)
		{
			init_quote_struct(token);
			expand(ms, token);
			// printf("Tras expansión: \"%s\"\n", token->content);
			token = retokenizer(token, ms, NULL, NULL);
		}
		token = token->next;
	}
	// printf("That was all the tokens\n");
	// print_tokens(ms->token);
	return (SUCCESS);
}

/* Inicializa la struct para la gestión de las comillas. */
static void	init_quote_struct(t_token *token)
{
	token->quotes = NULL;
	token->quotes = malloc(sizeof(t_quotes));
	if (!token->quotes)
		ms_quit(MALLOC_ERR);
	token->quotes->s = get_quotes(token->content, '\'');
	token->quotes->d = get_quotes(token->content, '"');
	token->quotes->s_on = OFF;
	token->quotes->d_on = OFF;
}

/* Devuelve un array int* con los valores de los index en los que en la string
'str' se encuentre el caracter 'get', está pensado para que 'get' sea \' o \".
Cierra el array con el valor -1 como terminador. */
static int	*get_quotes(char *str, char get)
{
	int	*array;
	int	len;
	int	i;
	int	j;

	len = ft_chrcount(str, get);
	array = malloc(sizeof(int) * (len + 1));
	if (!array)
		ms_quit(MALLOC_ERR);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == get)
			array[j++] = i;
		i++;
	}
	array[j] = -1;
	return (array);
}

/* Recorre el contenido del token proporcionado y llama a expand_and_update
si detecta un $ */
static void	expand(t_ms *ms, t_token *token)
{
	int		i;

	i = -1;
	while (token->content[++i])
	{
		// printf("X i = %d\n", i);
		if (token->content[i] == '\'' && token->quotes->d_on == OFF \
		&& is_valid_quote(i, token->quotes->s))
			token->quotes->s_on *= SWITCH;
		if (token->content[i] == '"' && token->quotes->s_on == OFF \
		&& is_valid_quote(i, token->quotes->d))
			token->quotes->d_on *= SWITCH;
		if (token->content[i] == '$' && token->quotes->s_on == OFF)
			token->content = expand_and_update(ms, token->content, \
			&i, token->quotes);
		if (!token->content[i]) // testing
			break;
		// printf("X i = %d\n", i);
		// printf("X str[i] = '%c'\n", token->content[i]);
		// printf("X %s\n", token->content);
	}
	return ;
}

/* Comprueba si el index recibido corresponde con uno de los valores
en el array recibido. Retorna 1 si lo encuentra y 0 si no.*/
int	is_valid_quote(int index, int *quote_array)
{
	int	i;

	i = 0;
	while (quote_array[i] != -1)
	{
		if (index == quote_array[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	is_active_quote(char *str, int index, t_quotes *q)
{
	if (index == 0) // Para reiniciar los estados de las quotes a OFF por si aca
	{
		q->d_on = OFF;
		q->s_on = OFF;
	}
	if (str[index] == '\'' && q->d_on == OFF && is_valid_quote(index, q->s))
	{
		q->s_on *= SWITCH;
		return (TRUE);
	}
	else if (str[index] == '"' && q->s_on == OFF && is_valid_quote(index, q->d))
	{
		q->d_on *= SWITCH;
		return (TRUE);
	}
	return (FALSE);
}
