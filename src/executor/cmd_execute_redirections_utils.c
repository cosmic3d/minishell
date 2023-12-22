/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_redirections_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:44:18 by jenavarr          #+#    #+#             */
/*   Updated: 2023/12/22 20:43:06 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	do_hrdc_loop(int tmp_fd, char *tmp_str, char *tmp_eof, int *xs) //PONER A INT
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
