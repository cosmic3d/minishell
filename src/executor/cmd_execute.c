/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:32:05 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/27 22:53:00 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  */
/* int	execute_cmd */
/* Esta función crea los archivos necesarios para las redirecciones.
Si ya existía el archivo, no hace nada. Si no existe, lo crea.
Si no existe y encima lo quieres crear en una carpeta que tampoco existe,
un error No such file or directory salta. */
int	create_redirection_files(t_cmdinfo	*cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i])
	{
		j = -1;
		while (++j < cmd[i].num_rd)
		{

		}
	}
}
