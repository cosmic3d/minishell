/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_home_expansor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:18:16 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/24 18:32:05 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quote_positions_home(t_quotes *quote, int len, int index);

char	*expand_home(t_ms *ms, char *str, int *i, t_quotes *quote)
{
	t_env	*homeenv;
	char	*home;
	char	*aux_str;
	char	*new_str;

	if ((str[*i + 1] && str[*i + 1] != ' ' && str[*i + 1] != '/') \
	|| (*i != 0 && str[*i - 1] != ' ' && str[*i - 1] != '/'))
		return (str);
	homeenv = env_find("HOME", ms->env);
	home = ms->home;
	if (homeenv && homeenv->content)
		home = homeenv->content;
	aux_str = ft_strljoin(str, *i, home, -1);
	if (!aux_str)
		ms_quit(MALLOC_ERR);
	new_str = ft_strljoin(aux_str, -1, str + *i + 1, -1);
	if (!new_str)
		ms_quit(MALLOC_ERR);
	free(aux_str);
	update_quote_positions_home(quote, ft_strlen(home), *i);
	*i += ft_strlen(home) - 1;
	return (new_str);
}

static void	update_quote_positions_home(t_quotes *quote, int len, int index)
{
	int	i;

	i = 0;
	while (quote->d[i] != -1)
	{
		if (quote->d[i] > index)
			quote->d[i] += len - 1;
		i++;
	}
	i = 0;
	while (quote->s[i] != -1)
	{
		if (quote->s[i] > index)
			quote->s[i] += len - 1;
		i++;
	}
	return ;
}
