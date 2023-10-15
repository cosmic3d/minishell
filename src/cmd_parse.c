/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:06:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/15 17:08:37 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Si existen comillas comprueba si son válidas
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
					return (FAILURE);
				if (str[i] == bracks)
					break ;
				i++;
			}
		}
	}
	return (SUCCESS);
}

//Crea los tokens y los va añadiendo a una linked list
void	tokenize(char *cmd_line, t_ms *ms)
{
	t_token	*last;
	int		i;
	int		new_token;
	//char	in_bracks;

	i = -1;
	new_token = -1;
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
				if (token_append(&ms->token) == FAILURE)
					exit(1);
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
