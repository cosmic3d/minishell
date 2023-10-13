/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:06:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/13 20:57:10 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->content);
		free(tmp);
		//tmp = NULL;
	}
	token = NULL;
}

int	valid_brackets(char *str)
{
	int		i;
	char	bracks;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			bracks = str[i++];
			while (42)
			{
				if (!str[i])
					return (0);
				if (str[i] == bracks)
					break ;
				i++;
			}
		}
	}
	return (1);
}

void	tokenize(char *cmd_line, t_ms *ms)
{
	t_token	*last;
	int		i;
	int		new_token;
	//char	in_bracks;

	i = -1;
	new_token = -1;
	//printf("CMD_LINE: %s\n", cmd_line);
	while (cmd_line[++i])
	{
		if (new_token == -1)
		{
			if (cmd_line[i] == ' ')
				continue ;
			else
				new_token = i;
		}
		else
		{
			if (cmd_line[i] == ' ' || (!cmd_line[i + 1] && i++ != -1)) //Creamos nuevo token si encontramos un espacio u otros símbolos que ya definiremos después
			{
				write(1, "Llega2\n", 8);
				if (token_append(ms->token) == FAILURE)
					exit(1);
				write(1, "Llega\n", 7);
				last = token_tail(ms->token);
				last->content = ft_substr(cmd_line, new_token, i - new_token);
				if (!last->content)
				{
					ms_error(MALLOC_ERR);
					exit(1);
				}
				//last->type =  get_token_type() //EN EL FUTURO
				new_token = -1;
			}
			// continue ;
		}

		// if (cmd_line[i] == '"' || cmd_line[i] == '\'')
		// {
		// 	in_bracks = cmd_line[i++];
		// 	while (cmd_line[i] != in_bracks)
		// 		i++;

		// }
	}
}

/* Añade un token a la linked list (la función genérica me da problemas creo) */
int	token_append(t_token *head)
{
	t_token	*new;
	t_token	*last;

	//write(1, "HOLIS2\n", 8);
	new = malloc(sizeof(t_token));
	if (!new)
	{
		ms_error(MALLOC_ERR);
		return (FAILURE);
	}
	//write(1, "HOLIS\n", 7);
	new->prev = NULL;
	new->next = NULL;
	if (head == NULL)
		head = new;
	else
	{
		write(1, "HOLIS3\n", 8);
		last = token_tail(head);
		write(1, "HOLIS4\n", 8);
		last->next = new;
		new->prev = last;
	}
	return (SUCCESS);
}

t_token	*token_tail(t_token *token)
{
	while (token->next != NULL)
		token = token->next;
	return (token);
}
