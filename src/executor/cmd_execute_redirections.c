/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:04:59 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/28 20:50:52 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Devuelve SUCCESS si el archivo existía y tenía permisos. */
static void	in_rds(t_redirection *rd_current, t_redirection **rd_in, int *xs)
{
	if (file_check(rd_current->str, F_OK) == TRUE)
	{
		if (file_check(rd_current->str, HAS_READ_PERMISSIONS) == TRUE)
		{
			*rd_in = rd_current;
			return ;
		}
		general_perror(rd_current->str, ": Permission denied\n", NULL, NULL);
		*xs = 1;
		return ;
	}
	general_perror(rd_current->str, ": No such file or directory", "\n", NULL);
	*xs = 1;
	return ;
}

/* Devuelve SUCCESS si el archivo existía y tenía permisos o si
no existía y se ha podido crear. */
static void	out_rds(t_redirection *rd_current, t_redirection **rd_out, int *xs)
{
	int	fd;

	if (file_check(rd_current->str, F_OK) == TRUE)
	{
		if (file_check(rd_current->str, HAS_WRITE_PERMISSIONS) == TRUE)
		{
			*rd_out = rd_current;
			return ;
		}
		general_perror(rd_current->str, ": Permission denied\n", NULL, NULL);
		*xs = 1;
		return ;
	}
	fd = open(rd_current->str, O_CREAT);
	if (fd < 0) //CHECKEAR QUE AL PROBSR CON UNA CARPETA DA ERROR DE NO SUCH FILE OR DIRECTORY
	{
		general_perror(rd_current->str, ": ", strerror(errno), "\n");
		*xs = 1;
		return ;
	}
	*rd_out = rd_current;
	return ;
}

/* Iteramos a través de todas las redirecciones de todos los comandos
y las evaluamos de izquierda a derecha. Si en alguna de ellas sucede
algún error, la función setea exit status a 1 y devuelve FAILURE.
Podemos proceder con la ejecución de los comandos. */
void	iterate_rds(t_cmdinfo	*cmd, int num_cmds, int *exit_status)
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
				in_rds(&cmd[i].rd[j], &cmd[i].rd_in, exit_status);
			else
				out_rds(&cmd[i].rd[j], &cmd[i].rd_out, exit_status);
		}
	}
	return ;
}
