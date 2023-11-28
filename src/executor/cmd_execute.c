/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:32:05 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/28 20:51:00 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Función que llama a otras para realizar todo el proceso
a seguir en la ejecución de los comandos. Devuelve SUCCESS si los
comandos se han ejecutado sin problema alguno. */
int	execute_cmds(t_ms *ms) //EN PROCESO
{
	iterate_rds(ms->cmd, ms->num_cmd, &ms->exit_status);
	return (SUCCESS);
}
