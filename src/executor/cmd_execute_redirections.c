/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:04:59 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/28 15:20:10 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int

/* Esta función crea los archivos necesarios para las redirecciones.
Si ya existía el archivo, no hace nada. Si no existe, lo crea.
Si no existe y encima lo quieres crear en una carpeta que tampoco existe,
un error No such file or directory salta. */
int	iterate_redirection_files(t_cmdinfo	*cmd, int num_cmds)
{
	int	i;
	int	j;

	i = -1;
	while (++i < num_cmds)
	{
		j = -1;
		while (++j < cmd[i].num_rd)
		{
			if (cmd[i].rd[j].type > REDIRECT_APPEND)
				continue ;
			if (file_check(cmd[i].rd[j].str, IS))
		}
	}
}
