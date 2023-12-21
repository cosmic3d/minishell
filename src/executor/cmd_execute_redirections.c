/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:04:59 by jenavarr          #+#    #+#             */
/*   Updated: 2023/12/21 21:34:28 by jenavarr         ###   ########.fr       */
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
			ms_perror(rd_i->str, "Is a directory", NULL, NULL);
			*xs = 1;
			return ;
		}
		if (file_check(rd_i->str, HAS_READ_PERMISSIONS) == TRUE)
		{
			*rd_in = rd_i;
			return ;
		}
		ms_perror(rd_i->str, "Permission denied", NULL, NULL);
		*xs = 1;
		return ;
	}
	ms_perror(rd_i->str, "No such file or directory", NULL, NULL);
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
		ms_perror(rd_i->str, "Permission denied", NULL, NULL);
		*xs = 1;
		return ;
	}
	if (ms_open(rd_i, &fd, xs) == FAILURE)
		return ;
	*rd_out = rd_i;
	close(fd);
	return ;
}

static void	do_hrdc(t_redirection *rd_i, int *xs, int i)
{
	int		tmp_fd;
	char	*tmp_eof;
	char	*tmp_str;

	tmp_eof = ft_strdup(rd_i->str);
	if (!tmp_eof || get_mshtmp_str(&rd_i->str, i) == FAILURE)
		ms_quit(MALLOC_ERR);
	if (ms_open(rd_i, &tmp_fd, xs) == FAILURE)
		return ;
	tmp_str = readline("> ");
	while (tmp_str && ft_strncmp(tmp_str, tmp_eof, ft_strlen(tmp_str)))
	{
		if (write(tmp_fd, tmp_str, ft_strlen(tmp_str)) < 0 && close(tmp_fd) < 1)
		{
			ms_perror(strerror(errno), NULL, NULL, NULL);
			*xs = 1;
			free(tmp_str);
			free(tmp_eof);
			return ;
		}
		free(tmp_str);
		tmp_str = readline("> ");
	}
	free(tmp_eof);
	close(tmp_fd);
}

static void	iterate_hrdcs(t_cmdinfo *cmd, int num_cmd, int *exit_status)
{
	int	i;
	int	j;

	i = -1;
	while (++i < num_cmd)
	{
		j = -1;
		// *exit_status = 0; //Porqué?
		while (++j < cmd[i].num_rd)
		{
			if (cmd[i].rd[j].type == REDIRECT_HEREDOC)
				do_hrdc(&cmd[i].rd[j], exit_status, i);
			if (*exit_status)
				break ;
		}
	}
}

/* Iteramos a través de todas las redirecciones de todos los comandos
y las evaluamos de izquierda a derecha. Si en alguna de ellas sucede
algún error, la función setea exit status a 1 y continua con el
siguiente comando en cuestión. */
void	iterate_rds(t_cmdinfo *cmd, int num_cmds, int *exit_status)
{
	int	i;
	int	j;

	i = -1;
	iterate_hrdcs(cmd, num_cmds, exit_status);
	while (++i < num_cmds)
	{
		j = -1;
		// *exit_status = 0; //Porqué?
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
