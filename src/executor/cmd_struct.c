/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:04:53 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/31 19:02:38 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_info(t_ms *ms)
{
	int	num_cmd;
	int	i;

	i = -1;
	num_cmd = get_num_cmds(ms->token);
	ms->cmd = (t_cmdinfo *)malloc(sizeof(t_cmdinfo) * num_cmd);
	if (!ms->cmd)
		return (FAILURE);
	while (++i < num_cmd) //EN PROCESO
	{

	}
}

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
