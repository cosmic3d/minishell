/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:11 by jenavarr          #+#    #+#             */
/*   Updated: 2023/12/05 12:15:33 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_struct_init(t_ms *ms);

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	argv[0] = NULL;
	argv = NULL;
	if (argc != 1)
		return (ms_error(ARGC_ERR));
	if (ms_struct_init(&ms) == FAILURE)
		return (FAILURE);
	if (env_list_init(&ms, envp) == FAILURE)
		return (FAILURE);
	disable_control_chars_echo();
	signal_handler();
	if (readline_loop(&ms))
		return (FAILURE);
	restore_terminal_settings();
	exit(EXIT_SUCCESS);
	return (0);
}

static int	ms_struct_init(t_ms *ms)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (errno)
	{
		ms_perror("malloc", strerror(errno), NULL, NULL);
		return (FAILURE);
	}
	ms->env = NULL;
	ms->token = NULL;
	ms->cmd = NULL;
	ms->pwd = pwd;
	ms->num_cmd = 0;
	ms->envp = NULL;
	ms->shlvl = 0;
	ms->exit_status = 0;
	return (SUCCESS);
}
