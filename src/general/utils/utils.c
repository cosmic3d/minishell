/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:29:35 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/22 20:42:51 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Función análoga a strlen, pero con char** en vez de char*
Devuelve la len de un char **array, asumiendo que este termina con un NULL */
int	ms_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	check_fds(void)
{
	int	fd;

	fd = open("testfile.msh", O_CREAT, D_PERMS);
	if (fd < 0)
	{
		ms_perror("open error: ", strerror(errno), NULL, NULL);
		exit(1);
	}
	close(fd);
	return ;
}

/* Limpia toda la terminal.
Son dos secuencias ANSI.
La primera posiciona el cursor en la esquina superior izquierda
de la terminal, mientras que la segunda elimina su contenido.
NOTA: No va nada (me voy a suicidar)*/
void	clearTerm(void) //eliminar esta mierda xd
{
	if (2 + 3 == 5)
		return ;
	/* rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay(); */
	/* printf("\033[H\033[J");
	printf("\033[2K\r"); */

    // Imprime caracteres de retroceso para borrar la línea del prompt
    //printf("\033[2K\r");
	/* printf("\033[H\033[J");
	printf("\033[A");
	printf("\033[2K"); //\033[H
	printf("\033[2J"); //\033[H
	printf("%s%s%s", "\033[A", "\033[2K", "\033[1J"); */
}

int	reset_received_signal(void)
{
	g_received_signal = -1;
	return (SUCCESS);
}
