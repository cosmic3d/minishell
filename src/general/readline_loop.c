/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:52:54 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/25 20:03:10 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*terminal_entry(int exit_status);

// Loop principal del minishell
int	readline_loop(t_ms *ms)
{
	char	*buffer;

	buffer = NULL;
	while (42)
	{
		if (buffer)
			free(buffer);
		buffer = terminal_entry(ms->exit_status);
		if (!buffer)
			return (1);
		if (!(tokenize(buffer, ms) == SUCCESS && \
		expansor(ms, ms->token) == SUCCESS && iterate_cmds(ms) == SUCCESS))
			continue ;
		execute_cmds(ms);
		erase_hrdc_files(ms->cmd, ms->num_cmd);
		free_tokens(&ms->token);
		free_cmd_structs(ms->cmd, ms->num_cmd);
	}
	rl_clear_history();
	return (0);
}

/* Función que se encarga de leer la entrada del usuario.
En el caso de que se encuentre NULL puede deberse a dos motivos:
1- Readline ha recibido un eof (Ctrl+D)
2- Error interno de readline */
static char	*terminal_entry(int exit_status)
{
	char	*buffer;

	signal_handler(INTERACTIVE);
	buffer = readline(CMDPROMPT);
	if (!buffer)
	{
		if (rl_eof_found)
		{
			if (isatty(STDIN))
				printf("%s%s%s%s", "\033[A", "\033[2K", CMDPROMPT, "exit\n");
			restore_terminal_settings();
			exit(exit_status);
		}
		ms_quit(MALLOC_ERR);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	restore_terminal_settings();
	if (buffer[0] != '\0')
		add_history(buffer);
	return (buffer);
}
