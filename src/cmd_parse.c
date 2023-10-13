/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:06:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/13 16:27:24 by jenavarr         ###   ########.fr       */
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
	int	i;
	int	two_simple;
	int	two_double;

	i = -1;
	two_double = 1;
	two_simple = 1;
	while (str[++i])
	{
		if (str[i] == '\'')
			two_simple *= -1;
		else if (str[i] == '\"')
			two_double *= -1;
	}
	if (two_double == -1 || two_simple == -1)
		return (0);
	return (1);
}
