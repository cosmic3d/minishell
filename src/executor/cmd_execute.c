/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:32:05 by jenavarr          #+#    #+#             */
/*   Updated: 2023/12/05 11:36:18 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	execution_loop(t_ms *ms, int fd[2])
// {
// 	for(i=0;i<numsimplecommands; i++) {
// 	  //redirect input
// 	  dup2(fdin, 0);
// 	  close(fdin);
// 	  //setup output
// 	  if (i == numsimplecommands){
// 		// Last simple command
// 		if(outfile){
// 		  fdout=open(outfile,â€¦â€¦);
// 		}
// 		else {
// 		  // Use default output
// 		  fdout=dup(tmpout);
// 		}
// 	  }

// 	   else {
// 		  // Not last
// 		  //simple command
// 		  //create pipe
// 		  int fdpipe[2];
// 		  pipe(fdpipe);
// 		  fdout=fdpipe[1];
// 		  fdin=fdpipe[0]; //FUNDAMENTAL
// 	   }// if/else

// 	   // Redirect output
// 	   dup2(fdout,1);
// 	   close(fdout);

// 	   // Create child process
// 	   ret=fork();
// 	   if(ret==0) {
// 		 execvp(scmd[i].args[0], scmd[i].args);
// 		 perror("Execvp");
// 		 _exit(1);
// 	   }
// 	 } //  for
// }

// static void	init_execution(t_ms *ms)
// {
// 	int	tmp[2];
// 	int	fd[2];

// 	//Duplicamos stdin y stdout para no perderlos y
// 	if (ms_dup(STDIN, -1, &tmp[STDIN], &ms->exit_status) == FAILURE)
// 		return ;
// 	if (ms_dup(STDOUT, -1, &tmp[STDOUT], &ms->exit_status) == FAILURE && close(tmp[STDIN]) <= 0)
// 		return ;
// 	if (!ms->cmd[0].rd_in)
// 	{
// 		if (ms_dup(tmp[STDIN], -1, &fd[STDIN], &ms->exit_status) == FAILURE)
// 			return ;
// 	}
// 	else if (ms_open(ms->cmd[0].rd_in, &fd[STDIN], &ms->exit_status) == FAILURE)
// 		return ;
// 	execution_loop(ms, fd);


// 	 //restore in/out defaults
// 	 if (ms_dup(tmp[STDIN], STDIN, NULL, &ms->exit_status) == FAILURE && close(tmp[STDIN]) <= 0 && close(tmp[STDOUT]) <= 0)
// 	 	return ;
// 	//HACER LA OTRA QUE QUEDA DE DUP2 PARA TMPOUT
// 	 dup2(tmpin,0);
// 	 dup2(tmpout,1);
// 	 close(tmpin);
// 	 close(tmpout);

// 	 if (!background) {
// 		// Wait for last command
// 		waitpid(ret, NULL);
// 	}
// } // execute

/* Función que llama a otras para realizar todo el proceso
a seguir en la ejecución de los comandos. Devuelve SUCCESS si los
comandos se han ejecutado sin problema alguno. PUEDE QUE SE CAMBIE
EL FUNCIONAMIENTO DE ESTA FUNCIÓN EN EL FUTURO */
int	execute_cmds(t_ms *ms) //EN PROCESO
{
	iterate_rds(ms->cmd, ms->num_cmd, &ms->exit_status);
	return (SUCCESS);
}
