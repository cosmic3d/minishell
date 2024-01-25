/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_redirections_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:44:18 by jenavarr          #+#    #+#             */
/*   Updated: 2024/01/25 18:42:58 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Obtenemos el string del nombre que representará al archivo del heredoc.*/
int	get_mshtmp_str(char **result, int i)
{
	char	*tmp_str;

	tmp_str = ft_itoa(i);
	if (!tmp_str)
		ms_quit(MALLOC_ERR);
	free(*result);
	*result = ft_strjoin("/tmp/mshtmp_", tmp_str);
	if (!(*result))
	{
		free(tmp_str);
		ms_quit(MALLOC_ERR);
	}
	free(tmp_str);
	return (SUCCESS);
}

/* Entramos en el bucle de un heredoc y leemos hasta que encontremos
la palabra especificada o hasta que sea interrumpido mediante una señal. */
int	do_hrdc_loop(int tmp_fd, char *tmp_str, char *tmp_eof, int *xs)
{
	int	eof_len;

	eof_len = ft_strlen(tmp_eof);
	while (tmp_str && !((int)ft_strlen(tmp_str) == eof_len && \
	!ft_strncmp(tmp_str, tmp_eof, ft_strlen(tmp_eof))))
	{
		if (write(tmp_fd, tmp_str, ft_strlen(tmp_str)) < 0 || \
		write(tmp_fd, "\n", 1) < 0)
		{
			ms_perror(strerror(errno), NULL, NULL, NULL);
			*xs = 1;
			break ;
		}
		free(tmp_str);
		tmp_str = readline("> ");
	}
	if (!tmp_str && !rl_eof_found && g_received_signal != SIGINT)
		ms_quit(MALLOC_ERR);
	else if (tmp_str)
		free(tmp_str);
	free(tmp_eof);
	close(tmp_fd);
	if (g_received_signal == SIGINT && reset_received_signal() == SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

/* Se encarga de eliminar los archivos temporales creados por heredoc,
si es que existen*/
int	erase_hrdc_files(t_cmdinfo *cmd, int num_cmd)
{
	int	i;
	int	j;

	i = -1;
	while (++i < num_cmd)
	{
		j = -1;
		while (++j < cmd[i].num_rd)
		{
			if (cmd[i].rd[j].type == REDIRECT_HEREDOC)
			{
				if (file_check(cmd[i].rd[j].str, F_OK) == TRUE && \
				unlink(cmd[i].rd[j].str) < 0)
				{
					ms_perror(strerror(errno), NULL, NULL, NULL);
					return (FAILURE);
				}
				break ;
			}
		}
	}
	return (SUCCESS);
}
