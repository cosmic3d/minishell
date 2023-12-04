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

// PROVISIONAL, printea el error_message al STDERR y retorna 1
int	ms_error(char *error_message)
{
	write(STDERR, "Error\n", 7);
	write(STDERR, error_message, ft_strlen(error_message));
	return (1);
}

void	export_perror(char *argument)
{
	write(STDERR, "minishell: export: `", 21);
	write(STDERR, argument, ft_strlen(argument));
	write(STDERR, "': not a valid identifier\n", 27);
}

// Printea el error y usa exit(EXIT_FAILURE); // necesitará t_ms *ms?
void	ms_quit(char *error_message)
{
	ms_error(error_message);
	restore_terminal_settings();
	rl_clear_history(); // ?
	exit(EXIT_FAILURE);
}

// void	ms_perror(t_ms *ms, char *program, char *error)
// {
// 	write(STDERR, "minishell: ", 12);
// 	write(STDERR, program, ft_strlen(program));
// 	write(STDERR, ": ", 2);
// 	write(STDERR, error, ft_strlen(error));
// }

// int	ms_error_quit(char *error, int exit_status, char *error)
// {

// }

// TO-DO:
/*
	- Necesitaremos un ms_error para salir de los programas que llamemos.
		Por lo que he visto, supongo que tendremos que liberar cosas de
		la pipe con la que llamemos al programa así que tendrá que ser
		una función especifica para eso.

	- Hay errores de los cuales solo necesitaremos un return en vez de
	un exit. Habrá que hacer esa función también.

	- Hay que estandarizar las funciones de error en general, seguramente
	ms_error cambie de nombre más adelante, o cambie su funcionamiento.

	- ?
*/
