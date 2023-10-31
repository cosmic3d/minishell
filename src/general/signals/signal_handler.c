/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:01:55 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/31 19:02:23 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios	g_original_termios;

/* Guarda los atributos actuales de la terminal en la global de arriba
y luego establece unos nuevos, desactivando el ECHOCTL que provoca ^C y ^\ */
void	disable_control_chars_echo(void)
{
	struct termios	new_termios;

	tcgetattr(0, &g_original_termios);
	new_termios = g_original_termios;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new_termios);
}

/* Restablece los atributos de la terminal.
Esto es importante porque de no hacerlo, incluso saliendo de
nuestro programa los atributos de la terminal no se restablecerán solos */
void	restore_terminal_settings(void)
{
	tcsetattr(0, TCSANOW, &g_original_termios);
}

/* Función para la señal SIGINT */
static void	signal_c(int signum)
{
	if (signum == CTRL_C)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	restore_terminal_settings();
	return ;
}

/* Función para la señal SIGQUIT */
static void	signal_backslash(int signum)
{
	if (signum == CTRL_BACKSLASH)
		restore_terminal_settings();
	return ;
}

// provisional
int	signal_handler(void)
{
	struct sigaction	sa_c;
	struct sigaction	sa_bs;

	sa_c.sa_handler = signal_c;
	sa_bs.sa_handler = signal_backslash;
	sigemptyset(&sa_c.sa_mask);
	sigemptyset(&sa_bs.sa_mask);
	sa_c.sa_flags = 0;
	sa_bs.sa_flags = 0;
	sigaction(CTRL_C, &sa_c, NULL);
	sigaction(CTRL_BACKSLASH, &sa_bs, NULL);
	return (1);
}
