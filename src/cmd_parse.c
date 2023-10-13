/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:06:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/13 18:11:10 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

static char	**ft_free(char **array, int k)
{
	while (k > 0)
		free(array[k--]);
	free(array[k]);
	free(array);
	return (NULL);
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

t_token	tokenize(char *cmd_line)
{
	t_token	tokens;
	int		i;
	int		new_token;
	char	in_bracks;

	i = -1;
	new_token = -1;
	while (cmd_line[++i])
	{
		if (cmd_line[i] != ' ' && new_token == -1)
			new_token = i;
		if (cmd_line[i] == '"' || cmd_line[i] == '\'')
		{
			in_bracks = cmd_line[i++];
			while ()
		}
	}
}
