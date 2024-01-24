/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:33:00 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/20 17:27:00 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Esta función nos permite escribir en stderror un mensaje personalizado.
Es cierto que tenemos un máximo de 4 argumentos,
pero deberían de ser suficientes.
Se imprime siempre minishell: delante. */
int	ms_perror(char *s1, char *s2, char *s3, char *s4)
{
	write(STDERR, "minishell: ", 11);
	if (s1)
	{
		write(STDERR, s1, ft_strlen(s1));
	}
	if (s2)
	{
		write(STDERR, ": ", 2);
		write(STDERR, s2, ft_strlen(s2));
	}
	if (s3)
	{
		write(STDERR, ": ", 2);
		write(STDERR, s3, ft_strlen(s3));
	}
	if (s4)
	{
		write(STDERR, ": ", 2);
		write(STDERR, s4, ft_strlen(s4));
	}
	write(STDERR, "\n", 1);
	return (1);
}

// Printea el error y usa exit(EXIT_FAILURE);
void	ms_quit(char *error_message)
{
	if (error_message)
	{
		write(STDERR, "Error\n", 7);
		write(STDERR, error_message, ft_strlen(error_message));
	}
	restore_terminal_settings();
	rl_clear_history();
	exit(EXIT_FAILURE);
}
