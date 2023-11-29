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
int	general_perror(char *s1, char *s2, char *s3, char *s4)
{
	write(STDERR_FILENO, "minishell: ", 12);
	if (s1)
		write(STDERR_FILENO, s1, ft_strlen(s1));
	if (s2)
		write(STDERR_FILENO, s2, ft_strlen(s2));
	if (s3)
		write(STDERR_FILENO, s3, ft_strlen(s3));
	if (s4)
		write(STDERR_FILENO, s4, ft_strlen(s4));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

// PROVISIONAL, printea el error_message al STDERR y retorna 1
int	ms_error(char *error_message)
{
	write(STDERR_FILENO, "Error\n", 7);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	return (1);
}

void	export_perror(char *argument)
{
	write(STDERR_FILENO, "minishell: export: `", 21);
	write(STDERR_FILENO, argument, ft_strlen(argument));
	write(STDERR_FILENO, "': not a valid identifier\n", 27);
}

// Printea el error y usa exit(EXIT_FAILURE); // necesitará t_ms *ms?
void	ms_quit(char *error_message)
{
	ms_error(error_message);
	restore_terminal_settings();
	exit(EXIT_FAILURE);
}

// void	ms_perror(t_ms *ms, char *program, char *error)
// {
// 	write(STDERR_FILENO, "minishell: ", 12);
// 	write(STDERR_FILENO, program, ft_strlen(program));
// 	write(STDERR_FILENO, ": ", 2);
// 	write(STDERR_FILENO, error, ft_strlen(error));
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
