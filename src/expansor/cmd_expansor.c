/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:27:34 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/14 19:15:01 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_quote_struct(t_token *token);
static int	*get_quotes(char *str, char get);
static void	expand(t_ms *ms, t_token *token);
static int	is_valid_quote(int index, int *s_quotes);

int	expansor(t_ms *ms, t_token *token)
{
	ms->shlvl = 1; // gcc no llores

	while (token)
	{
		if (token->type == TEXT) // Si el token es de tipo TEXT, usar el expansor
		{
			init_quote_struct(token);
			expand(ms, token);
			// retokenize(ms, token, token->content, &quotes);
		}
		token = token->next;
	}
	return (SUCCESS);
}

static void	init_quote_struct(t_token *token)
{
	token->quotes = malloc(sizeof(t_quotes));
	if (!token->quotes)
		ms_quit(MALLOC_ERR);
	token->quotes->s = get_quotes(token->content, '\'');
	token->quotes->d = get_quotes(token->content, '"');
	token->quotes->s_on = OFF;
	token->quotes->d_on = OFF;
}

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

static void	expand(t_ms *ms, t_token *token)
{
	int		i;

	i = -1;
	// for (int x = 0; token->quote->d[x] != -1; x++) //debug
	// 	printf("token->quote %d\n", token->quote->d[x]);
	while (token->content[++i])
	{
		if (token->content[i] == '\'' && token->quotes->d_on == OFF \
		&& is_valid_quote(i, token->quotes->s))
			token->quotes->s_on *= SWITCH;
		if (token->content[i] == '"' && token->quotes->s_on == OFF \
		&& is_valid_quote(i, token->quotes->d))
			token->quotes->d_on *= SWITCH;
		if (token->content[i] == '$' && token->quotes->s_on == OFF)
		{
			token->content = expand_and_update(ms, token->content, &i, token->quotes);
		}
	}
	return ;
}

static int	is_valid_quote(int index, int *array)
{
	int	i;

	i = 0;
	while (array[i] != -1)
	{
		if (index == array[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}
