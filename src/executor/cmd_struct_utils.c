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

#include "minishell.h"

/* Devuelve el número de argumentos detectados en un comando*/
int	get_num_arguments(t_token *token)
{
	int		text_count;
	t_token	*tmp;

	text_count = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type != TEXT)
		{
			tmp = tmp->next->next;
			continue ;
		}
		if (tmp->type == TEXT && tmp->hascontent == TRUE)
			text_count++;
		tmp = tmp->next;
	}
	return (text_count);
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

/* Establece la oflag de una redirección, la cual nos será
útil para más tarde al hacer open */
void	get_rd_oflag(t_redirection *rd)
{
	if (rd->type == REDIRECT_IN)
		rd->oflag = O_RDONLY;
	else if (rd->type == REDIRECT_HEREDOC)
		rd->oflag = O_CREAT | O_WRONLY | O_TRUNC;
	else if (rd->type == REDIRECT_OUT)
		rd->oflag = O_CREAT | O_WRONLY | O_TRUNC;
	else if (rd->type == REDIRECT_APPEND)
		rd->oflag = O_CREAT | O_WRONLY | O_APPEND;
	return ;
}
