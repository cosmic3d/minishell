/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:57:57 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/02 23:57:57 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/* Devuelve el número de argumentos detectados en un comando*/
int	get_num_arguments(t_token *token)
{
	int		text_count;
	t_token	*tmp;

	text_count = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == TEXT)
			text_count++;
		tmp = tmp->next;
	}
	return (text_count - get_num_redirections(token));
}

/* Devuelve el número de redirecciones detectadas en un comando*/
int	get_num_redirections(t_token *token)
{
	int	rd_count;

	rd_count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type != TEXT)
			rd_count++;
		token = token->next;
	}
	return (rd_count);
}

/* Devuelve el número de comandos detectados en los tokens*/
int	get_num_cmds(t_token *token)
{
	int		pipes;

	pipes = 0;
	while (token)
	{
		if (token->type == PIPE)
			pipes++;
		token = token->next;
	}
	return (pipes + 1);
}

/* Cuenta todos los argumentos de un comando, los aloja
en un puntero, los rellena y devuelve el puntero.
En caso de no haber argumentos devuelve NULL.
En caso de ocurrir algún error, libera todo y hace exit*/
char	**get_arguments(t_token *token)
{
	char	**args;
	int		arg_count;
	int		i;

	i = -1;
	arg_count = get_num_arguments(token);
	if (!arg_count)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		ms_quit(MALLOC_ERR);
	args[arg_count] = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type != TEXT)
		{
			token = token->next->next;
			continue ;
		}
		args[++i] = ft_strdup(token->content);
		if (!args[i])
			ms_quit(MALLOC_ERR);
		token = token->next;
	}
	return (args);
}

/* Cuenta todas las redirecciones de un comando, las aloja
en un puntero, las rellena y devuelve el puntero.
En caso de no haber redirecciones devuelve NULL.
En caso de ocurrir algún error, libera todo y hace exit*/
t_redirection *get_redirections(t_token *token, int rd_count)
{
	t_redirection	*rd;

	if (!rd_count)
		return (NULL);
	rd = (t_redirection *)malloc(sizeof(t_redirection) * (rd_count--));
	if (!rd)
		ms_quit(MALLOC_ERR);
	while (token && token->type != PIPE)
	{
		if (token->type == TEXT)
		{
			token = token->next;
			continue ;
		}
		rd[rd_count].type = token->type;
		rd[rd_count].str = ft_strdup(token->next->content);
		if (!rd[rd_count--].str)
			ms_quit(MALLOC_ERR);
		token = token->next->next;
	}
	return (rd);
}
