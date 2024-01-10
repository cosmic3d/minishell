/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:41:33 by jenavarr          #+#    #+#             */
/*   Updated: 2024/01/10 17:24:59 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Asigna el resultado de dup o dup2 a un *newfd. Si hay algún error,
lo imprime en STDERROR y devuelve FAILURE.
También se encarga de establecer exit status a 1 en caso de error y
de */
int	ms_dup(int fd, int fd2, int *newfd, int *xs)
{
	int	retfd;

	if (fd2 != -1)
		retfd = dup2(fd, fd2);
	else
		retfd = dup(fd);
	if (retfd >= 0)
	{
		if (fd2 != -1)
			close(fd);
		else
			*newfd = retfd;
		return (SUCCESS);
	}
	ms_perror("dup", strerror(errno), NULL, NULL);
	*xs = 1;
	return (FAILURE);
}

/* Es un open pero de una redirección. Abre el archivo al que apunta
esa redirección con las flags especificadas y con los permisos default.
Si algo falla entonces errorcito, cambiamos exit status y devolvemos.*/
int	ms_open(t_redirection *rd, int *fd, int *xs)
{
	*fd = open(rd->str, rd->oflag, D_PERMS);
	if (*fd < 0)
	{
		ms_perror(rd->str, strerror(errno), NULL, NULL);
		*xs = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

/* ¿Cansado de pasarte de 25 líneas porque estás acostumbrado a programar
como un ser humano normal? ¡No te preocupes! Esta función hace exactamente lo
mismo que la de pipe pero aquí para que no ocupe líneas en tu importante
función principal :) */
int	ms_pipe(int fd[2], int *xs)
{
	int	pipefd[2];

	if (pipe(pipefd) != SUCCESS)
	{
		ms_perror("pipe", strerror(errno), NULL, NULL);
		*xs = 1;
		return (FAILURE);
	}
	fd[STDIN] = pipefd[STDIN];
	fd[STDOUT] = pipefd[STDOUT];
	return (SUCCESS);
}

/* Adivina :3. Sí, esta función también hace exactamente lo mismo que fork
pero así ahorramos líneas y de paso manejamos errores. (Gracias 42 por
limitarme a expresar la voluntad de mi alma en menos de 25 líneas) */
int	ms_fork(int *forkret, int *xs)
{
	*forkret = fork();
	if (*forkret == -1)
	{
		ms_perror("fork", strerror(errno), NULL, NULL);
		*xs = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

/* Seteamos el exit status de cualquier hijo que termine.
Además también imprimimos el mensajito que da SIGQUIT.*/
int	set_exit_status(int forkret, int num_cmd)
{
	int	child_status;
	int	xs;
	int	i;

	xs = 1;
	child_status = 0;
	i = -1;
	while (++i < num_cmd)
	{
		if (waitpid(-1, &child_status, 0) == forkret)
		{
			if (WIFEXITED(child_status)) //Terminó correctamente
				xs = WEXITSTATUS(child_status);
			else if (WIFSIGNALED(child_status)) //Terminó por una señal
				xs = 128 + WTERMSIG(child_status);
			else if (WIFSTOPPED(child_status)) // Fue detenido por una señal
				xs = 128 + WSTOPSIG(child_status);
			if (xs - SIGQUIT == 128)
				write(1, "Quit: 3\n", 8);
		}
		if (WIFSIGNALED(child_status) && WTERMSIG(child_status) == SIGINT)
			write(1, "\n", 1);
	}
	return (xs);
}
