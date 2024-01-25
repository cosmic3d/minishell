/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:29:35 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/25 17:43:16 by jenavarr         ###   ########.fr       */
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

/* Resetea la global */
int	reset_received_signal(void)
{
	g_received_signal = -1;
	return (SUCCESS);
}
