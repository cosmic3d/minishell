/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:04:53 by jenavarr          #+#    #+#             */
/*   Updated: 2024/01/25 18:39:54 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Libera todas las estructuras de los comandos. */
void	free_cmd_structs(t_cmdinfo *cmdinfo, int cmd_num)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd_num)
	{
		j = -1;
		while (cmdinfo[i].args && cmdinfo[i].args[++j])
		{
			free(cmdinfo[i].args[j]);
			cmdinfo[i].args[j] = NULL;
		}
		if (cmdinfo[i].args)
			free(cmdinfo[i].args);
		cmdinfo[i].args = NULL;
		j = -1;
		while (cmdinfo[i].rd && ++j < cmdinfo[i].num_rd)
		{
			free(cmdinfo[i].rd[j].str);
			cmdinfo[i].rd[j].str = NULL;
		}
		free(cmdinfo[i].rd);
	}
	free(cmdinfo);
	cmdinfo = NULL;
}

/* Cuenta todos los argumentos de un comando, los aloja
en un puntero, los rellena y devuelve el puntero.
En caso de no haber argumentos devuelve NULL.
En caso de ocurrir algún error, libera todo y hace exit*/
char	**get_arguments(t_token *token, int arg_count, int i, char **args)
{
	if (!args)
		ms_quit(MALLOC_ERR);
	args[arg_count] = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type != TEXT)
		{
			token = token->next;
			if (token)
				token = token->next;
			continue ;
		}
		if (token->hascontent == FALSE)
		{
			token = token->next;
			continue ;
		}
		args[++i] = ft_strdup(token->content);
		if (!args[i])
			ms_quit(MALLOC_ERR);
		token = token->next;
	}
	return (args);
}

/* Cuenta todas las redirecciones de un comando, las aloja
en un puntero, las rellena y devuelve el puntero.
En caso de no haber redirecciones devuelve NULL.
En caso de ocurrir algún error, libera todo y hace exit*/
t_redirection	*get_redirections(t_token *token, int rd_count)
{
	t_redirection	*rd;
	int				i;

	if (!rd_count)
		return (NULL);
	rd = (t_redirection *)malloc(sizeof(t_redirection) * (rd_count));
	if (!rd)
		ms_quit(MALLOC_ERR);
	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == TEXT)
		{
			token = token->next;
			continue ;
		}
		rd[i].type = token->type;
		get_rd_oflag(&rd[i]);
		rd[i].str = ft_strdup(token->next->content);
		if (!rd[i++].str)
			ms_quit(MALLOC_ERR);
		token = token->next->next;
	}
	return (rd);
}

/* Esta función se encarga de rellenar la estructura del comando y de devolver
un puntero al inicio del siguiente comando*/
static t_token	*get_cmd_info(t_token *token, t_cmdinfo *cmdinfo)
{
	int	arg_count;

	cmdinfo->num_rd = get_num_redirections(token);
	cmdinfo->rd = get_redirections(token, cmdinfo->num_rd);
	arg_count = get_num_arguments(token);
	cmdinfo->args = NULL;
	if (arg_count)
		cmdinfo->args = get_arguments(token, arg_count, -1, \
	(char **)malloc(sizeof(char *) * (arg_count + 1)));
	cmdinfo->exists = TRUE;
	if (!cmdinfo->args)
		cmdinfo->exists = FALSE;
	cmdinfo->next_cmd = NULL;
	cmdinfo->fdin = STDIN_FILENO;
	cmdinfo->fdout = STDOUT_FILENO;
	cmdinfo->rd_in = NULL;
	cmdinfo->rd_out = NULL;
	cmdinfo->cmd = NULL;
	if (cmdinfo->args)
		cmdinfo->cmd = cmdinfo->args[0];
	while (token && token->type != PIPE)
		token = token->next;
	if (token)
		token = token->next;
	return (token);
}

/* Esta función es la iteradora principal de las estructuras de los comandos.
Aquí reservaremos las estructuras necesarias e iteraremos a través de ellas
hasta que se acaben.
En las iteraciones, llamaremos a una función auxiliar que se encargará de
guardar toda la información necesaria en ese comando a partir de un
token hasta el siguiente pipe o NULL.*/
int	iterate_cmds(t_ms *ms)
{
	int		i;
	t_token	*tmp;

	i = -1;
	ms->num_cmd = get_num_cmds(ms->token);
	tmp = ms->token;
	ms->cmd = (t_cmdinfo *)malloc(sizeof(t_cmdinfo) * (ms->num_cmd));
	if (!ms->cmd)
		ms_quit(MALLOC_ERR);
	while (++i < ms->num_cmd && tmp)
	{
		tmp = get_cmd_info(tmp, &ms->cmd[i]);
		if (tmp)
			ms->cmd[i].next_cmd = &ms->cmd[i + 1];
	}
	return (SUCCESS);
}
