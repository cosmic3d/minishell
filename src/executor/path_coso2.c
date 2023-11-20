/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_coso2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:08:45 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/20 16:26:36 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define TYPE_CMD 1
#define TYPE_FILE 0

#define ERR_NO_SUCH_FILE 127
#define ERR_CMD_NOT_FOUND 127

#define NO_SUCH_FILE "No such file or directory"
#define CMD_NOT_FOUND "command not found"

t_ppath	*get_program(char *cmd, int *exit_status, t_ms *ms)
{
	t_ppath	*data;

	data = init_ppath_data();
	if (!cmd || !cmd[0])
		return (no_cmd_case(ms, data))

/* La cosa está complicada */

	return (data);
}

t_ppath	*no_cmd_case(t_ms *ms, t_ppath *data)
{
	if (data->cmd_type == TYPE_FILE)
		data->exit_status = ERR_NO_SUCH_FILE;
	else if (data->cmd_type == TYPE_CMD)
		data->exit_status = ERR_CMD_NOT_FOUND;
	return (data);
}

t_ppath	*init_ppath_data(t_ms *ms)
{
	t_ppath *data;
	t_env	*path;

	data = malloc(sizeof(t_ppath));
	if (!data)
		ms_quit(MALLOC_ERR);
	data->filepath = NULL;
	data->error_message = NULL;
	data->exit_status = SUCCESS;
	data->path_exists = TRUE;
	path = env_find("PATH", ms->env);
	if (!path || !path->content || !path->content[0])
		data->path_exists = FALSE;
	data->cmd_type = TYPE_FILE;
	if (data->path_exists == FALSE)
		data->cmd_type = TYPE_CMD;
	return (data);
}
