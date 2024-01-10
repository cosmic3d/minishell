/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:52:54 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/10 15:37:58 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prototipo provisional // Nombre provisional
int	readline_loop(t_ms *ms)
{
	char	*buffer;

	while (42)
	{
		buffer = terminal_entry();
		if (!buffer)
			return (1);
		if (tokenize(buffer, ms) == FAILURE)
		{
			free(buffer);
			continue ;
		}
		if (expansor(ms, ms->token) == FAILURE) // testing
			continue ; // testing
		//print_tokens(ms->token);
		if (iterate_cmds(ms) == FAILURE)
			continue ;
		// execute_cmds(ms);
		// exit(ms->exit_status);
		// debug, para llamar builtins
		//ms->exit_status = llamar_builtins(ms);
		//// debugging find path coso
		/* if (ms->exit_status == -1)
		{
			ms->exit_status = 0;
			char *path = get_pathname(ms->token->content, &ms->exit_status, ms);
			printf("path: = %s\n", path);
		} */
		execute_cmds(ms);
		////
		erase_hrdc_files(ms->cmd, ms->num_cmd);
		free(buffer);
		free_tokens(&ms->token);
		free_cmd_structs(ms->cmd, ms->num_cmd); //EN EL FUTURO CERCANO
	}
	rl_clear_history();
	return (0);
}

// Prototipo provisional // Nombre provisional
char	*terminal_entry(void)
{
	char	*buffer;

	signal_handler(INTERACTIVE);
	buffer = readline(CMDPROMPT);
	if (!buffer)
	{
		// Una de dos:
		// Error de readline
		// NULL enviado a readline
		//Al recibir Ctrl+D (eof), volvemos a la línea anterior y la eliminamos para luego imprimir exit
		if (rl_eof_found)
		{
			if (isatty(STDIN))
				printf("%s%s%s%s", "\033[A", "\033[2K", CMDPROMPT, "exit\n");
			restore_terminal_settings();
			exit(SUCCESS);
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
