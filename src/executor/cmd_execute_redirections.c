/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:04:59 by jenavarr          #+#    #+#             */
/*   Updated: 2024/01/25 02:30:12 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Se encarga de dar error en determinadas ocasiones
(falta de permisos, el archivo no existe, es una carpeta...) */
static void	in_rds(t_redirection *rd_i, t_redirection **rd_in, int *xs)
{
	if (!rd_i->str[0])
	{
		*xs = 1;
		ms_perror(rd_i->str, AMBIGUOUS_REDIRECT, NULL, NULL);
		return ;
	}
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
			if (rd_i->type == REDIRECT_HEREDOC)
				rd_i->oflag = O_RDONLY;
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

	if (!rd_i->str[0])
	{
		*xs = 1;
		ms_perror(rd_i->str, AMBIGUOUS_REDIRECT, NULL, NULL);
		return ;
	}
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

/* Preparamos el terreno para poder realizar el heredoc.
Entre otras cosas abrimos el archivo para poder escribir en él y el
manejador de señales pasa a ser el de heredoc */
static int	do_hrdc(t_redirection *rd_i, int *xs, int i)
{
	int		tmp_fd;
	int		tmp_stdin;
	char	*tmp_eof;
	char	*tmp_str;

	tmp_eof = ft_strdup(rd_i->str);
	if (!tmp_eof || get_mshtmp_str(&rd_i->str, i) == FAILURE)
		ms_quit(MALLOC_ERR);
	if (ms_open(rd_i, &tmp_fd, xs) == FAILURE)
	{
		free(tmp_eof);
		return (FAILURE);
	}
	tmp_stdin = dup(STDIN);
	if (tmp_stdin < 0 && close(tmp_fd) <= 0)
		ms_quit("Dup error");
	signal_handler(HEREDOC);
	tmp_str = readline("> ");
	tmp_fd = do_hrdc_loop(tmp_fd, tmp_str, tmp_eof, xs);
	if (dup2(tmp_stdin, STDIN) < 0 && close(tmp_stdin) <= 0)
		ms_quit("Dup error");
	close(tmp_stdin);
	signal(SIGINT, SIG_IGN);
	return (tmp_fd);
}

/* Iteramos a través de todos los heredocs de todos los comandos,
ya que aunque solo queremos el último de cada comando, todos los demás
se deben de realizar igualmente */
int	iterate_hrdcs(t_cmdinfo *cmd, int num_cmd, int *exit_status)
{
	int	i;
	int	j;
	int	aux;

	i = -1;
	while (++i < num_cmd)
	{
		aux = 0;
		j = -1;
		while (++j < cmd[i].num_rd)
		{
			if (cmd[i].rd[j].type == REDIRECT_HEREDOC)
				if (do_hrdc(&cmd[i].rd[j], &aux, i) == FAILURE)
					return (FAILURE);
			if (aux)
			{
				*exit_status = aux;
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

/* Iteramos a través de todas las redirecciones de un comando
y las evaluamos de izquierda a derecha. Si en alguna de ellas sucede
algún error, la función setea exit status a 1 y continua con el
siguiente comando en cuestión. */
int	iterate_rds(t_cmdinfo *cmd, int *exit_status)
{
	int	i;
	int	aux;

	i = -1;
	aux = 0;
	while (++i < cmd->num_rd)
	{
		if (cmd->rd[i].type > REDIRECT_APPEND)
			in_rds(&cmd->rd[i], &cmd->rd_in, &aux);
		else
			out_rds(&cmd->rd[i], &cmd->rd_out, &aux);
		if (aux)
		{
			*exit_status = aux;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
/* int	iterate_rds(t_cmdinfo *cmd, int num_cmds, int *exit_status)
{
	int	i;
	int	j;
	int	aux;

	i = -1;
	while (++i < num_cmds)
	{
		j = -1;
		aux = 0;
		while (++j < cmd[i].num_rd)
		{
			if (cmd[i].rd[j].type > REDIRECT_APPEND)
				in_rds(&cmd[i].rd[j], &cmd[i].rd_in, &aux);
			else
				out_rds(&cmd[i].rd[j], &cmd[i].rd_out, &aux);
			if (aux)
			{
				*exit_status = aux;
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
} */
