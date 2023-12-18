/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:11 by jenavarr          #+#    #+#             */
/*   Updated: 2023/12/18 02:41:16 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	argv[0] = NULL;
	argv = NULL;
	clearTerm();
	if (argc != 1 || argv)
		return (ms_error(ARGC_ERR));
	env_init(&ms, envp);
	disable_control_chars_echo();
	signal_handler(INTERACTIVE);
	if (readline_loop(&ms))
		return (FAILURE);
	restore_terminal_settings();
	exit(EXIT_SUCCESS);
	return (0);
}
