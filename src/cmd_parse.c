/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:06:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/15 20:55:14 by jenavarr         ###   ########.fr       */
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
					return (FALSE);
				if (str[i] == bracks)
					break ;
				i++;
			}
		}
	}
	return (TRUE);
}

//Crea los tokens y los va añadiendo a una linked list
void	tokenize(char *cmd_line, t_ms *ms)
{
	t_token	*last;
	int		i;
	int		nt; //El primer caracter del new token (puta norminette)

	i = -1;
	nt = -1;
	while (cmd_line[++i])
	{
		if (nt == -1)
		{
			if (cmd_line[i] == ' ')
				continue ;
			else
				nt = i;
		}
		if (nt != -1) //METER TODO ESTO EN OTRA FUNCIÓN
		{
			if (get_token(&i, cmd_line))
			{
				if (token_append(&ms->token) == FAILURE)
					exit(1);
				last = token_tail(ms->token);
				last->content = ft_substr(cmd_line, nt, i - nt + 1);
				if (!last->content)
				{
					ms_error(MALLOC_ERR);
					exit(1);
				}
				//last->type =  get_token_type() //EN EL FUTURO
				nt = -1;
			}
		}
	}
}

//Aquí se definen los limitadores entre token y token
int	get_token(int *i, char *cmd_line)
{
	char	tmp;

	if (!in_x("<>|\'\"", cmd_line[*i]) && \
	(in_x(" <>|\'\"", cmd_line[*i + 1]) || !cmd_line[*i + 1]))
		return (TRUE);
	if (in_x("\'\"", cmd_line[*i]))
	{
		tmp = cmd_line[*i];
		*i = *i + 1;
		while (cmd_line[*i] && cmd_line[*i] != tmp)
			*i = *i + 1;
	}
	else if (in_x("<>", cmd_line[*i]))
	{
		tmp = cmd_line[*i];
		if (cmd_line[*i + 1] == tmp)
			*i = *i + 1;
	}
	else if (cmd_line[*i] != '|')
		return (FALSE);
	return (TRUE);
}
