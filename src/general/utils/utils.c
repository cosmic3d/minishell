/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:29:35 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/06 19:29:55 by jenavarr         ###   ########.fr       */
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
