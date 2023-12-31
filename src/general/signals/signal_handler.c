/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:01:55 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/18 18:03:48 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf("SALIENDO\n"); //ELIMINAR
	/* rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay(); */
	exit(signum);
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
	{
		sa_c.sa_handler = signal_action_heredoc;
		sa_bs.sa_handler = signal_action_heredoc;
	}
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
