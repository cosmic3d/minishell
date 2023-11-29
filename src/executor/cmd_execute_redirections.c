/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:04:59 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/29 21:44:49 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Se encarga de dar error en determinadas ocasiones
(falta de permisos, el archivo no existe, es una carpeta...) */
static void	in_rds(t_redirection *rd_i, t_redirection **rd_in, int *xs)
{
	if (file_check(rd_i->str, F_OK) == TRUE)
	{
		if (file_check(rd_i->str, IS_DIRECTORY) == TRUE)
		{
			general_perror(rd_i->str, ": Is a directory", NULL, NULL);
			*xs = 1;
			return ;
		}
		if (file_check(rd_i->str, HAS_READ_PERMISSIONS) == TRUE)
		{
			*rd_in = rd_i;
			return ;
		}
		general_perror(rd_i->str, ": Permission denied", NULL, NULL);
		*xs = 1;
		return ;
	}
	general_perror(rd_i->str, ": No such file or directory", NULL, NULL);
	*xs = 1;
	return ;
}

/* Se encarga de crear los archivos si es necesario y de dar error en
determinadas ocasiones (falta de permisos, el archivo no existe,
es una carpeta...) */
static void	out_rds(t_redirection *rd_i, t_redirection **rd_out, int *xs)
{
	int	fd;

	if (file_check(rd_i->str, F_OK) == TRUE && \
	file_check(rd_i->str, IS_DIRECTORY) == FALSE)
	{
		if (file_check(rd_i->str, HAS_WRITE_PERMISSIONS) == TRUE)
		{
			*rd_out = rd_i;
			return ;
		}
		general_perror(rd_i->str, ": Permission denied", NULL, NULL);
		*xs = 1;
		return ;
	}
	fd = open(rd_i->str, O_WRONLY | O_CREAT, DEFAULT_PERMISSIONS);
	if (fd < 0)
	{
		general_perror(rd_i->str, ": ", strerror(errno), NULL);
		*xs = 1;
		return ;
	}
	*rd_out = rd_i;
	close(fd);
	return ;
}

/* Iteramos a través de todas las redirecciones de todos los comandos
y las evaluamos de izquierda a derecha. Si en alguna de ellas sucede
algún error, la función setea exit status a 1 y continua con el
siguiente comando en cuestión. */
void	iterate_rds(t_cmdinfo	*cmd, int num_cmds, int *exit_status)
{
	int	i;
	int	j;

	i = -1;
	while (++i < num_cmds)
	{
		j = -1;
		*exit_status = 0;
		while (++j < cmd[i].num_rd)
		{
			if (cmd[i].rd[j].type > REDIRECT_APPEND)
				in_rds(&cmd[i].rd[j], &cmd[i].rd_in, exit_status);
			else
				out_rds(&cmd[i].rd[j], &cmd[i].rd_out, exit_status);
			if (*exit_status)
				break ;
		}
	}
	return ;
}
