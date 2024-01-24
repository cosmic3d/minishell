/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:01:55 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/24 21:23:21 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_received_signal = 0; //Se puede inicializar una global con un valor o norminette se queja?

/* Función para las señales cuando estamos en modo interactivo */
static void	signal_action_interactive(int signum)
{
	if (signum == CTRL_C)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

/* Función para las señales cuando estamos en modo heredoc */
static void	signal_action_heredoc(int signum)
{
	g_received_signal = signum;
	close(STDIN);
	return ;
}

// Maneja las señales
int	signal_handler(int mode)
{
	struct sigaction	sa_c;
	struct sigaction	sa_bs;

	sa_c.sa_handler = signal_action_interactive;
	sa_bs.sa_handler = signal_action_interactive;
	if (mode == HEREDOC)
		sa_c.sa_handler = signal_action_heredoc;
	sigemptyset(&sa_c.sa_mask);
	sigemptyset(&sa_bs.sa_mask);
	sa_c.sa_flags = 0;
	sa_bs.sa_flags = 0;
	if (sigaction(CTRL_C, &sa_c, NULL) == -1 || \
	sigaction(CTRL_BACKSLASH, &sa_bs, NULL) == -1)
	{
		ms_perror("sigaction", strerror(errno), NULL, NULL);
		ms_quit(NULL);
	}
	return (1);
}
