/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:04:53 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/15 17:34:09 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_structs(t_cmdinfo *cmdinfo, int cmd_num)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd_num)
	{
		j = -1;
		while (cmdinfo[i].args && cmdinfo[i].args[++j])
		{
			free(cmdinfo[i].args[j]);
			cmdinfo[i].args[j] = NULL;
		}
		if (cmdinfo[i].args)
			free(cmdinfo[i].args);
		cmdinfo[i].args = NULL;
		j = -1;
		while (cmdinfo[i].rd && ++j < cmdinfo[i].num_rd)
		{
			free(cmdinfo[i].rd[j].str);
			cmdinfo[i].rd[j].str = NULL;
		}
		free(cmdinfo[i].rd);
	}
	free(cmdinfo);
	cmdinfo = NULL;
}

/* Esta función se encarga de rellenar la estructura del comando y de devolver
un puntero al inicio del siguiente comando*/
static t_token	*get_cmd_info(t_token *token, t_cmdinfo *cmdinfo)
{
	cmdinfo->num_rd = get_num_redirections(token);
	cmdinfo->rd = get_redirections(token, cmdinfo->num_rd);
	cmdinfo->args = get_arguments(token);
	cmdinfo->next_cmd = NULL;
	if (cmdinfo->args)
		cmdinfo->cmd = cmdinfo->args[0];
	while (token && token->type != PIPE)
		token = token->next;
	if (token)
		token = token->next;
	return (token);
}

/* Esta función es la iteradora principal de las estructuras de los comandos.
Aquí reservaremos las estructuras necesarias e iteraremos a través de ellas
hasta que se acaben.
En las iteraciones, llamaremos a una función auxiliar que se encargará de
guardar toda la información necesaria en ese comando a partir de un
token hasta el siguiente pipe o NULL.*/
int	iterate_cmds(t_ms *ms)
{
	int	i;
	t_token	*tmp;

	i = -1;
	ms->num_cmd = get_num_cmds(ms->token);
	tmp = ms->token;
	ms->cmd = (t_cmdinfo *)malloc(sizeof(t_cmdinfo) * (ms->num_cmd));
	if (!ms->cmd)
		ms_quit(MALLOC_ERR);
	while (++i < ms->num_cmd && tmp) //EN PROCESO
	{
		tmp = get_cmd_info(tmp, &ms->cmd[i]);
		if (tmp)
			ms->cmd[i].next_cmd = &ms->cmd[i + 1];
	}
	print_cmd_structs(ms->cmd, ms->num_cmd);
	return (SUCCESS);
}

