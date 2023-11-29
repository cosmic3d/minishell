/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:11 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/29 16:17:31 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	usleep(1000000); // debug
	argv[0] = NULL;
	argv = NULL;
	if (argc != 1 || argv)
		return (ms_error(ARGC_ERR));
	environment_init(&ms, envp);
	disable_control_chars_echo();
	signal_handler();
	if (readline_loop(&ms))
		return (FAILURE);
	restore_terminal_settings();
	exit(EXIT_SUCCESS);
	return (0);
}
