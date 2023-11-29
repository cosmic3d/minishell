/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:52:54 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/29 11:50:59 by apresas-         ###   ########.fr       */
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
		// debug, para llamar builtins
		ms->exit_status = llamar_builtins(ms);
		//// debugging find path coso
		if (ms->exit_status == -1)
		{
			char *path = command_to_file_path(ms->token->content, &ms->exit_status, ms);
			printf("path: = %s\n", path);
		}
		////
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

	buffer = readline(CMDPROMPT);
	if (!buffer)
	{
		// Una de dos:
		// Error de readline
		// NULL enviado a readline

		//Al recibir Ctrl+D (eof), volvemos a la línea anterior y la eliminamos para luego imprimir exit
		if (rl_eof_found)
		{
			printf("%s%s%s%s", "\033[A", "\033[2K", CMDPROMPT, "exit\n");
			restore_terminal_settings();
			exit(SUCCESS);
		}
		ms_quit(MALLOC_ERR);
	}
	if (buffer[0] != '\0')
		add_history(buffer);
	return (buffer);
}
