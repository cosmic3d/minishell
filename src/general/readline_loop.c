/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:52:54 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/03 04:06:10 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prototipo provisional // Nombre provisional
int	readline_loop(t_ms *ms)
{
	char	*buffer;

	while (42)
	{
		disable_control_chars_echo();
		buffer = terminal_entry();
		if (!buffer)
			return (1);
		if (tokenize(buffer, ms) == FAILURE)
			continue ;
		//print_tokens(ms->token);
		if (iterate_cmds(ms) == FAILURE)
			continue ;
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

	disable_control_chars_echo();
	buffer = readline(CMDPROMPT);
	if (!buffer)
	{
		// Una de dos:
		// Error de readline
		// NULL enviado a readline

		//Al recibir Ctrl+D (eof), volvemos a la línea anterior y la eliminamos para luego imprimir exit
		if (rl_eof_found)
			printf("%s%s%s%s", "\033[A", "\033[2K", CMDPROMPT, "exit\n");
		restore_terminal_settings();
		return (NULL);
	}
	if (buffer[0] != '\0')
		add_history(buffer);
	return (buffer);
}
