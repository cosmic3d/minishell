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
	/* if (check_tokens(ms) == SUCCESS)
		return (SUCCESS);
	free_tokens(&ms->token);
	return (FAILURE); */ //DE MOMENTO ASÍ
	return (SUCCESS);
}

//Aquí se definen los limitadores entre token y token
int	get_token(int *i, char *cmd_line)
{
	char	tmp;

	if (!in_x("<>|", cmd_line[*i]) && in_x("\"\'", cmd_line[*i + 1]))
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
		if (in_x("\'\"", cmd_line[*i + 1]))
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

/*Esta función se encargará de comprobar que no existan erorres de sintaxis,
parejas de comillas incompletas... Entre otras cosas feas.

Si devuelve FAILURE quiere decir que ha habido
algún error de ese tipo en algún token.

Si se da el caso, esta función NO liberará nada. Lo único de lo que se encarga
esta función aparte de comprobar errores es de eliminar las comillas del anterior
string y de igualar este nuevo string alojado al puntero de content del token.*/
//int	check_tokens(t_ms *ms)//COMENTALA SI TE DA PROBLEMAS
//{
	/*1. Se comprueba el token_type
	  2. En función del token_type se comprueba si el siguiente es adecuado
	  3. Si el token es de tipo texto se intentan eliminar las comillas.
	  4. Se devuelve FAILURE si algo falla*/
	//return (SUCCESS);
//}
