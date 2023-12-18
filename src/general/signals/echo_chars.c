/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 02:35:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/12/18 02:36:16 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Guarda los atributos actuales de la terminal en la global de arriba
y luego establece unos nuevos, desactivando el ECHOCTL que provoca ^C y ^\ */
void	disable_control_chars_echo(void)
{
	struct termios	new_termios;

	tcgetattr(0, &new_termios);
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new_termios);
}

/* Restablece los atributos de la terminal.
Esto es importante porque de no hacerlo, incluso saliendo de
nuestro programa los atributos de la terminal no se restablecerán solos */
void	restore_terminal_settings(void)
{
	struct termios	new_termios;

	tcgetattr(0, &new_termios);
	new_termios.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &new_termios);
}
