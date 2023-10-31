/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:04:53 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/31 20:42:33 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Esta función es la iteradora principal de las estructuras de los comandos.
Aquí reservaremos las estructuras necesarias e iteraremos a través de ellas
hasta que se acaben.
En las iteraciones, llamaremos a una función auxiliar que se encargará de
guardar toda la información necesaria en ese comando a partir de un
token hasta el siguiente pipe o NULL.*/
int	iterate_cmds(t_ms *ms)
{
	int	num_cmd;
	int	i;
	t_token *tmp;

	i = -1;
	num_cmd = get_num_cmds(ms->token);
	tmp = ms->token;
	ms->cmd = (t_cmdinfo *)malloc(sizeof(t_cmdinfo) * num_cmd);
	if (!ms->cmd)
		return (FAILURE);
	while (++i < num_cmd) //EN PROCESO
		tmp = get_cmd_info(tmp, &ms->cmd[i]);
}

t_token	*get_cmd_info(t_token *token, t_cmdinfo *cmdinfo) //MIRA EXECUTOR EN TRELLO PARA SABER QUÉ PLANEO
{

}

/* Devuelve el número de comandos detectados en los tokens*/
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
