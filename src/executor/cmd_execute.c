/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:32:05 by jenavarr          #+#    #+#             */
/*   Updated: 2023/12/12 18:04:14 by jenavarr         ###   ########.fr       */
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
		if (ms_pipe(fd, xs) == FAILURE)
			return (FAILURE);
		fd[STDIN] = pipefd[STDIN];
		if (!cmd->rd_out)
			fd[STDOUT] = pipefd[STDOUT];
		else if (close(pipefd[STDOUT]) <= 0 && ms_open(cmd->rd_out, \
		&fd[STDOUT], xs) == FAILURE && close(pipefd[STDIN]) <= 0) /* Si hay un archivo, cerramos el extremo de escritura del pipe para que el siguiente
			comando reciba un EOF y no lea nada de la pipe de lectura */
			return (FAILURE);
		if (cmd->next_cmd->rd_in && close(fd[STDIN]) <= 0 && \
		ms_open(cmd->next_cmd->rd_in, &fd[STDIN], xs) == FAILURE && \
		close(fd[STDOUT]) <= 0)
			return (FAILURE);
		return (SUCCESS);
	}
	if (!cmd->rd_out && ms_dup(tmp[STDOUT], -1, &fd[STDOUT], xs) == FAILURE)
		return (FAILURE);
	if (cmd->rd_out && \
	ms_open(cmd->rd_out, &fd[STDOUT], xs) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/* Una vez realizado el fork, se substituye en el hijo el proceso actual por
el comando en cuestión y esperamos a que acabe con waitpid.
Cuando el proceso haya terminado o sido detenido de cualquier forma
guardamos su exit status / señal con el que terminó en nuestro exit status*/
static int	manage_child(int forkret, t_cmdinfo *cmd, t_ms *ms)
{
	int	child_status;

	if (forkret == 0) //Es el proceso hijo
	{
		cmd->cmd = command_to_file_path(cmd->cmd, &ms->exit_status, ms);
		execve(cmd->cmd, cmd->args, ms->envp);
		ms_perror("execve", strerror(errno), NULL, NULL); // Si llega hasta aquí es que execve ha fallado :)
		ms_quit("Execve failed\n"); //ms quit no me gusta, hay que adaptarla a ms_perror
		return (FAILURE);
	}
	if (waitpid(forkret, &child_status, 0) == -1 && \
	ms_perror("waitpid", strerror(errno), NULL, NULL))
		return (FAILURE);
	else if (WIFEXITED(child_status)) //Terminó correctamente
		ms->exit_status = WEXITSTATUS(child_status);
	else if (WIFSIGNALED(child_status)) //Terminó por una señal
		ms->exit_status = 128 + WTERMSIG(child_status);
	else if (WIFSTOPPED(child_status)) // Fue detenido por una señal
		ms->exit_status = 128 + WSTOPSIG(child_status);
	else // Es raro que entre aquí, pero puede pasar. Hay algún que otro caso en que se puede reanudar un hijo con SIGCONT y otras cosas raras.
		ms_perror(cmd->cmd, "Child process error\n", NULL, NULL);
	/* COMMENT: No estoy seguro de la diferencia entre WIFSIGNALED y WIFSTOPPED,
	pero la hay y en cualquiera de los casos guardamos el exit status*/
	return (SUCCESS);
}

/* Ejecutamos todos los comandos en un bucle hasta que ya no haya más o
hasta que ocurra algún error con alguna función importante como fork, waitpid,
dup...En caso de fallo de esas funciones, la ejecución de los comandos termina y
el mensaje de error de turno es impreso. */
static int	execution_loop(t_ms *ms, int fd[2], int tmp[2])
{
	int	i;
	int	forkret;

	i = -1;
	while (++i < ms->num_cmd)
	{
		if (ms_dup(fd[STDIN], STDIN, NULL, &ms->exit_status) == FAILURE && \
		close(fd[STDIN]) <= 0)
			return (FAILURE);
		if (get_cmd_inout(&ms->cmd[i], fd, tmp, &ms->exit_status) == FAILURE)
			return (FAILURE);
		if (ms_dup(fd[STDOUT], STDOUT, NULL, &ms->exit_status) == FAILURE && \
		close(fd[STDOUT]) <= 0)
			return (FAILURE);
		if (ms_fork(&forkret, &ms->exit_status) == FAILURE)
			return (FAILURE);
		if (manage_child(forkret, &ms->cmd[i], ms) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
 	/* for(i=0;i<numsimplecommands; i++) {
 	  //redirect input
	  dup2(fdin, 0);
 	  close(fdin);
 	  //setup output
 	  if (i == numsimplecommands){
 		// Last simple command
 		if(outfile){
 		  fdout=open(outfile,giggity);
 		}
 		else {
 		  // Use default output
 		  fdout=dup(tmpout);
 		}
 	  }

 	   else {
 		  // Not last
 		  //simple command
 		  //create pipe
 		  int fdpipe[2];
 		  pipe(fdpipe);
 		  fdout=fdpipe[1];
 		  fdin=fdpipe[0]; //FUNDAMENTAL
 	   }// if/else

 	   // Redirect output
 	   dup2(fdout,1);
 	   close(fdout);

 	   // Create child process
 	   ret=fork();
 	   if(ret==0) {
 		 execvp(scmd[i].args[0], scmd[i].args);
 		 perror("Execvp");
 		 _exit(1);
}
	 } //  for
	waitpid(ret, NULL); */
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
	if (ms_dup(STDIN, -1, &tmp[STDIN], &ms->exit_status) == FAILURE)
		return (FAILURE);
	if (ms_dup(STDOUT, -1, &tmp[STDOUT], &ms->exit_status) == FAILURE && \
	close(tmp[STDIN]) <= 0)
		return (FAILURE);
	//Duplicar el stdin en caso de que exista un archivo
	if (!ms->cmd[0].rd_in)
	{
		//Si no existe una redirección de input para el primer comando,
		//quiere decir que por defecto fd[STDIN] es STDIN
		if (ms_dup(tmp[STDIN], -1, &fd[STDIN], &ms->exit_status) == FAILURE && \
		close(tmp[STDIN]) <= 0 && close(tmp[STDOUT]) <= 0)
			return (FAILURE);
	}
	//Si existe una redirección de input, abrimos ese archivo en fd[STDIN]
	else if (ms_open(ms->cmd[0].rd_in, &fd[STDIN], &ms->exit_status) == FAILURE \
	&& close(tmp[STDIN]) <= 0 && close(tmp[STDOUT]) <= 0)
		return (FAILURE);
	//Llamamos al bucle de ejecución de los comandos para que los ejecute todos
	//ASEGURATE DE QUE TENGAS EL PATH CORRECTO PARA LOS COMANDOS ANTES DE LLAMAR AQUÍ (/bin/ls)
	execution_loop(ms, fd, tmp);
	//Restauramos stdin y stdout para que apunten de nuevo a la terminal
	if (ms_dup(tmp[STDIN], STDIN, NULL, &ms->exit_status) == FAILURE && \
	close(tmp[STDIN]) <= 0 && close(tmp[STDOUT]) <= 0)
		return (FAILURE);
	if (ms_dup(tmp[STDOUT], STDOUT, NULL, &ms->exit_status) == FAILURE && \
	close(tmp[STDOUT]) <= 0)
		return (FAILURE);
	return (SUCCESS);
}

/* Función que llama a otras para realizar todo el proceso
a seguir en la ejecución de los comandos. Devuelve SUCCESS si los
comandos se han ejecutado sin problema alguno. PUEDE QUE SE CAMBIE
EL FUNCIONAMIENTO DE ESTA FUNCIÓN EN EL FUTURO */
int	execute_cmds(t_ms *ms) //EN PROCESO
{
	iterate_rds(ms->cmd, ms->num_cmd, &ms->exit_status); //DEBERÍA DE PARAR LA EJECUCIÓN DE LOS COMANDOS SI ALGO DE AQUÍ FALLA? COMPRUEBALO EN LOS MACS DEL CAMPUS
	if (init_execution(ms) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
