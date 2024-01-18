/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:32:05 by jenavarr          #+#    #+#             */
/*   Updated: 2024/01/18 18:00:41 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Se escoge cuál será el stdin del siguiente comando y el stdout del
comando actual. Para esto, primero comprobamos si no somos el último
comando. En tal caso, por defecto el stdin y el stdout serán el de la pipe.
Si somos el último, por defecto el stdin será el de la pipe y el stdout será
la propia terminal.
Después de asignar las pipes, comprobamos las redirecciones ya que priorizan
sobre estas, las cuales serán sobreescritas.
SI HAY ALGÚN ERROR EN ALGÚN COMANDO QUE NO SEA EL ÚLTIMO, LOS FILE DESCRIPTORS DE LA PIPE SE CIERRAN
*/
static int get_cmd_inout(t_cmdinfo *cmd, int fd[2], int tmp[2], int *xs)
{
	int	pipefd[2];

	if (cmd->next_cmd) //No es el último comando
	{
		if (ms_pipe(pipefd, xs) == FAILURE)
			return (FAILURE);
		fd[STDIN] = pipefd[STDIN];
		if (!cmd->rd_out)
			fd[STDOUT] = pipefd[STDOUT];
		else if (close(pipefd[STDOUT]) <= 0 && ms_open(cmd->rd_out, \
		&fd[STDOUT], xs) == FAILURE && close(pipefd[STDIN]) <= 0) /* Si hay un archivo, cerramos el extremo de escritura del pipe para que el siguiente
			comando reciba un EOF y no lea nada de la pipe de lectura */
			return (FAILURE);
		if (cmd->next_cmd->rd_in && close(fd[STDIN]) <= 0 && \
		ms_open(cmd->next_cmd->rd_in, &fd[STDIN], xs) \
		== FAILURE && close(fd[STDOUT]) <= 0)
			return (FAILURE);
		return (SUCCESS);
	}
	if (tmp[STDOUT] == -1)
		fd[STDOUT] = STDOUT;
	else if (!cmd->rd_out && ms_dup(tmp[STDOUT], -1, &fd[STDOUT], xs) == FAILURE)
		return (FAILURE);
	else if (cmd->rd_out && ms_open(cmd->rd_out, &fd[STDOUT], xs) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/* Una vez realizado el fork, se substituye en el hijo el proceso actual por
el comando en cuestión y esperamos a que acabe con waitpid.
Cuando el proceso haya terminado o sido detenido de cualquier forma
guardamos su exit status / señal con el que terminó en nuestro exit status*/
static int	manage_child(t_cmdinfo *cmd, t_ms *ms, int tmp[2])
{
	if (ms->forkret == 0) //Es el proceso hijo
	{
		close(tmp[STDIN]);
		close(tmp[STDOUT]);
		// close(STDIN);
		signal_handler(HEREDOC);
		tmp[0] = exec_builtin(ms, cmd);
		if (tmp[0] != -1)
			exit(tmp[0]);
		//write(2, "No es builtin\n", 14);
		cmd->cmd = get_pathname(cmd->cmd, &ms->exit_status, ms);
		if (!cmd->cmd)
			exit(_CMD_NOT_FOUND);
		ms->envp = env_list_to_envp(ms->env);
		if (!ms->envp)
			ms_quit(MALLOC_ERR);
		execve(cmd->cmd, cmd->args, ms->envp);
		ms_perror("execve", strerror(errno), NULL, NULL); // Si llega hasta aquí es que execve ha fallado :)
		ms_quit(NULL);
	}
	else if (ms->forkret == -2)
		ms->exit_status = exec_builtin(ms, cmd);
	/* if (isatty(STDOUT) == FALSE)
		close(STDOUT); */
	// if (ms->forkret != -2)
	// 	ms->exit_status = set_exit_status(ms->forkret, cmd->cmd);
	return (SUCCESS);
}

/* Ejecutamos todos los comandos en un bucle hasta que ya no haya más o
hasta que ocurra algún error con alguna función importante como fork, waitpid,
dup...En caso de fallo de esas funciones, la ejecución de los comandos termina y
el mensaje de error de turno es impreso. */
static int	execution_loop(t_ms *ms, int fd[2], int tmp[2])
{
	int	i;

	i = -1;
	while (++i < ms->num_cmd)
	{
		if (!ms->cmd[i].cmd)
			continue ;
		ms->forkret = -2;
		if (fd[STDIN] != STDIN && ms_dup(fd[STDIN], STDIN, \
		NULL, &ms->exit_status) == FAILURE && close(fd[STDIN]) <= 0)
			return (FAILURE);
		if (get_cmd_inout(&ms->cmd[i], fd, tmp, &ms->exit_status) == FAILURE)
			return (FAILURE);
		if (fd[STDOUT] != STDOUT && ms_dup(fd[STDOUT], STDOUT, \
		NULL, &ms->exit_status) == FAILURE && close(fd[STDOUT]) <= 0)
			return (FAILURE);
		if ((ms->num_cmd > 1 || is_builtin(ms->cmd[i].cmd) == FALSE) && \
		ms_fork(&ms->forkret, &ms->exit_status) == FAILURE)
			return (FAILURE);
		if (manage_child(&ms->cmd[i], ms, tmp) == FAILURE)
			return (FAILURE);
	}
	// provisional Albert
	int aux = set_exit_status(ms->forkret, ms->num_cmd);
	if (aux != -1)
		ms->exit_status = aux;
	//
	// Original:
	// ms->exit_status = set_exit_status(ms->forkret, ms->num_cmd);
	//
	return (SUCCESS);
}

/* Función previa al bucle de ejecución de los comandos. Se encarga de guardar
una copia de STDIN y STDOUT para luego al terminar el bucle restablecerlos.
También establece el STDIN del primer comando.
En caso de error, se devuelve FAILURE.
Un error en alguna de estas funciones es fatal y no nos permite continuar con
la ejecución de los comandos, aunque puede que sí con nuestro programa.
Esto puede suceder si nos limitan los file descriptors disponibles con
ulimit -n 4 por ejemplo.
SE REALIZARÁN PRUEBAS EN EL FUTURO PARA DECIDIR QUÉ HACER*/
static int	init_execution(t_ms *ms)
{
	int	tmp[2];
	int	fd[2];
	//Duplicamos stdin y stdout para no perderlos
	tmp[STDIN] = -1;
	tmp[STDOUT] = -1;
	if ((ms->num_cmd > 1 || ms->cmd[0].rd_in) && ms_dup(STDIN, -1, \
	&tmp[STDIN], &ms->exit_status) == FAILURE)
		return (FAILURE);
	if ((ms->num_cmd > 1 || ms->cmd[0].rd_out) && ms_dup(STDOUT, -1, \
	&tmp[STDOUT], &ms->exit_status) == FAILURE && close(tmp[STDIN]) <= 0)
		return (FAILURE);
	//Duplicar el stdin en caso de que exista un archivo
	if (!ms->cmd[0].rd_in)
		fd[STDIN] = STDIN;
	//Si existe una redirección de input, abrimos ese archivo en fd[STDIN]
	else if (ms_open(ms->cmd[0].rd_in, &fd[STDIN], &ms->exit_status) \
	== FAILURE && close(tmp[STDIN]) <= 0 && close(tmp[STDOUT]) <= 0)
		return (FAILURE);
	//Llamamos al bucle de ejecución de los comandos para que los ejecute todos
	execution_loop(ms, fd, tmp);
	//Restauramos stdin y stdout para que apunten de nuevo a la terminal
	if (tmp[STDIN] != -1 && ms_dup(tmp[STDIN], STDIN, NULL, &ms->exit_status) \
	== FAILURE && close(tmp[STDIN]) <= 0 && close(tmp[STDOUT]) <= 0)
		return (FAILURE);
	if (tmp[STDOUT] != -1 && ms_dup(tmp[STDOUT], STDOUT, \
	NULL, &ms->exit_status) == FAILURE && close(tmp[STDOUT]) <= 0)
		return (FAILURE);
	return (SUCCESS);
}

/* Función que llama a otras para realizar todo el proceso
a seguir en la ejecución de los comandos. Devuelve SUCCESS si los
comandos se han ejecutado sin problema alguno. PUEDE QUE SE CAMBIE
EL FUNCIONAMIENTO DE ESTA FUNCIÓN EN EL FUTURO */
int	execute_cmds(t_ms *ms) //EN PROCESO
{
	if (iterate_rds(ms->cmd, ms->num_cmd, &ms->exit_status) == FAILURE)
		return (FAILURE);
	if (init_execution(ms) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
