/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:01:55 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/26 21:13:40 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios	g_original_termios;

void	disable_control_chars_echo(void)
{
	struct termios	new_termios;

	tcgetattr(0, &g_original_termios);
	new_termios = g_original_termios;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new_termios);
}

void	restore_terminal_settings(void)
{
	tcsetattr(0, TCSANOW, &g_original_termios);
}

static void	signal_tal(int signum)
{
	if (signum == CTRL_C)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	restore_terminal_settings();
}

// provisional
int	signal_handler(void)
{
	signal(CTRL_C, signal_tal);
	signal(CTRL_BACKSLASH, signal_tal);
	return (1);
}
