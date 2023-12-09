/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:32:05 by jenavarr          #+#    #+#             */
/*   Updated: 2023/12/09 04:42:42 by jenavarr         ###   ########.fr       */
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
*/
static int get_cmd_inout(t_cmdinfo *cmd, int fd[2], int tmp[2], int *xs)
{
	int	pipefd[2];

	if (cmd->next_cmd)
	{
		if (cmd->next_cmd->rd_in && \
		ms_open(cmd->next_cmd->rd_in, &fd[STDIN], xs) == FAILURE)
			return (FAILURE);
		else if (!cmd->next_cmd->rd_in)
		{
			if (pipe(pipefd) != SUCCESS)
				return (FAILURE);
			fd[STDIN] = pipefd[STDIN];
			if (!cmd->rd_out)
				fd[STDOUT] = pipefd[STDOUT];
			else if (ms_open(cmd->rd_out, &fd[STDOUT], xs) == FAILURE && \
			close(pipefd[STDOUT]) <= 0) /* Si hay un archivo, cerramos el extremo de escritura del pipe para que el siguiente
			comando reciba un EOF y no lea nada de la pipe de lectura */
				return (FAILURE);
		}
		return (SUCCESS);
	}
	if (!cmd->rd_out && ms_dup(tmp[STDOUT], -1, &fd[STDOUT], xs) == FAILURE)
		return (FAILURE);
	if (cmd->rd_out && \
	ms_open(cmd->rd_out, &fd[STDOUT], xs) == FAILURE)
		return (FAILURE);
}


static int	execution_loop(t_ms *ms, int fd[2])
{
	int	i;

	i = -1;
	while (++i < ms->num_cmd)
	{
		//REALIZAR FUNCIÓN QUE ESTABLEZCA EL FD CORRECTO PARA STDIN Y STDOUT
		if (ms_dup(fd[STDIN], STDIN, NULL, &ms->exit_status) == FAILURE && \
		close(fd[STDIN]) <= 0)
			return (FAILURE);

	}
 	for(i=0;i<numsimplecommands; i++) {
 	  //redirect inpu
	  dup2(fdin, 0);
 	  close(fdin);
 	  //setup output
 	  if (i == numsimplecommands){
 		// Last simple command
 		if(outfile){
 		  fdout=open(outfile,â€¦â€¦);
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
	waitpid(ret, NULL);
}

static void	init_execution(t_ms *ms)
{
	int	tmp[2];
	int	fd[2];
	//Duplicamos stdin y stdout para no perderlos
	if (ms_dup(STDIN, -1, &tmp[STDIN], &ms->exit_status) == FAILURE)
		return ;
	if (ms_dup(STDOUT, -1, &tmp[STDOUT], &ms->exit_status) == FAILURE && \
	close(tmp[STDIN]) <= 0)
		return ;
	//Duplicar el stdin en caso de que exista un archivo
	if (!ms->cmd[0].rd_in)
	{
		//Si no existe una redirección de input para el primer comando,
		//quiere decir que por defecto fd[STDIN] es STDIN
		if (ms_dup(tmp[STDIN], -1, &fd[STDIN], &ms->exit_status) == FAILURE && \
		close(tmp[STDIN]) <= 0 && close(tmp[STDOUT]) <= 0)
			return ;
	}
	//Si existe una redirección de input, abrimos ese archivo en fd[STDIN]
	else if (ms_open(ms->cmd[0].rd_in, &fd[STDIN], &ms->exit_status) == FAILURE \
	&& close(tmp[STDIN]) <= 0 && close(tmp[STDOUT]) <= 0)
		return ;
	//Llamamos al bucle de ejecución de los comandos para que los ejecute todos
	//ASEGURATE DE QUE TENGAS EL PATH CORRECTO PARA LOS COMANDOS ANTES DE LLAMAR AQUÍ (/bin/ls)
	execution_loop(ms, fd);
	//Restauramos stdin y stdout para que apunten de nuevo a la terminal
	if (ms_dup(tmp[STDIN], STDIN, NULL, &ms->exit_status) == FAILURE && \
	close(tmp[STDIN]) <= 0 && close(tmp[STDOUT]) <= 0)
		return ;
	if (ms_dup(tmp[STDOUT], STDOUT, NULL, &ms->exit_status) == FAILURE && \
	close(tmp[STDOUT]) <= 0)
		return ;
}// execute
/* Función que llama a otras para realizar todo el proceso
a seguir en la ejecución de los comandos. Devuelve SUCCESS si los
comandos se han ejecutado sin problema alguno. PUEDE QUE SE CAMBIE
EL FUNCIONAMIENTO DE ESTA FUNCIÓN EN EL FUTURO */
int	execute_cmds(t_ms *ms) //EN PROCESO
{
	iterate_rds(ms->cmd, ms->num_cmd, &ms->exit_status);
	return (SUCCESS);
}
