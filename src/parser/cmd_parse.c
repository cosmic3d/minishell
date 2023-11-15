/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:06:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/20 18:36:51 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Crea los tokens y los va añadiendo a una linked list
int	tokenize(char *cmd_line, t_ms *ms)
{
	int		i;
	int		nt; //El primer caracter del new token (puta norminette)

	i = -1;
	nt = -1;
	ms->token = NULL;
	if (!valid_brackets(cmd_line))
		return (FAILURE);
	while (cmd_line[++i])
	{
		if (nt == -1)
		{
			if (cmd_line[i] == ' ')
				continue ;
			else
				nt = i;
		}
		if (nt != -1)
			add_token(cmd_line, &i, &nt, ms);
	}
	free(cmd_line);
	if (check_tokens(ms) == SUCCESS)
		return (SUCCESS);
	free_tokens(&ms->token);
	return (FAILURE);
}

//Aquí se definen los limitadores entre token y token
int	get_token(int *i, char *cmd_line)
{
	char	tmp;

	if (!in_x("<>|\"\'", cmd_line[*i]) && in_x("\"\'", cmd_line[*i + 1]))
		return (FALSE);
	if (!in_x("<>|\'\"", cmd_line[*i]) && \
	(in_x(" <>|\'\"", cmd_line[*i + 1]) || !cmd_line[*i + 1]))
		return (TRUE);
	if (in_x("\'\"", cmd_line[*i]))
	{
		tmp = cmd_line[*i];
		*i = *i + 1;
		while (cmd_line[*i] && cmd_line[*i] != tmp)
			*i = *i + 1;
		if ((!in_x("<>| ", cmd_line[*i + 1]) && cmd_line[*i + 1]))
			return (FALSE);
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

//Devuelve el tipo de token
int	get_token_type(char *str)
{
	if (!ft_strncmp(str, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(str, ">", 2))
		return (REDIRECT_OUT);
	else if (!ft_strncmp(str, ">>", 3))
		return (REDIRECT_APPEND);
	else if (!ft_strncmp(str, "<", 2))
		return (REDIRECT_IN);
	else if (!ft_strncmp(str, "<<", 3))
		return (REDIRECT_HEARDOC);
	return (TEXT);
}

/*Una vez se sabe cuál es el token se añade a la lista,
además de hacer el substr y de asignarle el tipo*/
void	add_token(char *cmd_line, int *i, int *nt, t_ms *ms)
{
	t_token	*last;

	if (get_token(i, cmd_line))
	{
		if (token_append(&ms->token) == FAILURE)
		{
			ms_error(MALLOC_ERR);
			exit(1);
		}
		last = token_tail(ms->token);
		last->content = ft_substr(cmd_line, *nt, *i - *nt + 1);
		if (!last->content)
		{
			ms_error(MALLOC_ERR);
			exit(1);
		}
		last->type = get_token_type(last->content);
		*nt = -1;
	}
}
