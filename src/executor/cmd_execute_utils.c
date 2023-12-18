/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:41:33 by jenavarr          #+#    #+#             */
/*   Updated: 2023/12/18 17:19:21 by apresas-         ###   ########.fr       */
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
	ms_perror("dup error", strerror(errno), NULL, NULL);
	*xs = 1;
	return (FAILURE);
}

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

int	ms_pipe(int fd[2], int *xs)
{
	int	pipefd[2];

	if (pipe(pipefd) != SUCCESS)
	{
		ms_perror(strerror(errno), NULL, NULL, NULL);
		*xs = 1;
		return (FAILURE);
	}
	fd[STDIN] = pipefd[STDIN];
	fd[STDOUT] = pipefd[STDOUT];
	return (SUCCESS);
}

int	ms_fork(int *forkret, int *xs)
{
	*forkret = fork();
	if (*forkret == -1)
	{
		ms_perror(strerror(errno), NULL, NULL, NULL);
		*xs = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	set_exit_status(int forkret, char *cmdname)
{
	int	child_status;
	int	xs;
	int	tmp_debug;

	xs = 1;
	tmp_debug = 0;
	while (waitpid(forkret, &child_status, 0) == -1)
	{
		/* ms_perror("waitpid", strerror(errno), NULL, NULL);
		ms_quit("waitpid error"); */
	}
	if (WIFEXITED(child_status)) //Terminó correctamente
	{
		xs = WEXITSTATUS(child_status);
		printf("1: EXIT STATUS: %i\n", xs);
	}
	else if (WIFSIGNALED(child_status)) //Terminó por una señal
	{
		xs = 128 + WTERMSIG(child_status);
		tmp_debug = xs - 128;
		printf("2: EXIT STATUS: 128 + %i\n", tmp_debug);
		printf("2: EXIT STATUS: %i\n", xs);
	}
	else if (WIFSTOPPED(child_status)) // Fue detenido por una señal
	{
		xs = 128 + WSTOPSIG(child_status);
		tmp_debug = xs - 128;
		printf("2: EXIT STATUS: 128 + %i\n", tmp_debug);
		printf("3: EXIT STATUS: %i\n", xs);
	}
	else // Es raro que entre aquí, pero puede pasar. Hay algún que otro caso en que se puede reanudar un hijo con SIGCONT y otras cosas raras.
		ms_perror(cmdname, "Child process error", NULL, NULL);
	/* COMMENT: No estoy seguro de la diferencia entre WIFSIGNALED y WIFSTOPPED,
	pero la hay y en cualquiera de los casos guardamos el exit status*/
	return (xs);
}
