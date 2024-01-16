/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llamar_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:44:01 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/16 18:55:36 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "exit"))
		return (TRUE);
	else if (!ft_strcmp(str, "echo"))
		return (TRUE);
	else if (!ft_strcmp(str, "env"))
		return (TRUE);
	else if (!ft_strcmp(str, "cd"))
		return (TRUE);
	else if (!ft_strcmp(str, "export"))
		return (TRUE);
	else if (!ft_strcmp(str, "pwd"))
		return (TRUE);
	else if (!ft_strcmp(str, "unset"))
		return (TRUE);
	return (FALSE);
}

// provisional
int	exec_builtin(t_ms *ms, t_cmdinfo *cmd)
{
	if (!ft_strcmp(cmd->cmd, "exit"))
		return (ms_exit(cmd->args, ms->exit_status));
	else if (!ft_strcmp(cmd->cmd, "echo"))
		return (ms_echo(cmd->args));
	else if (!ft_strcmp(cmd->cmd, "env"))
		return (ms_env(ms));
	else if (!ft_strcmp(cmd->cmd, "cd"))
		return (ms_cd(ms, cmd->args));
	else if (!ft_strcmp(cmd->cmd, "export"))
		return (ms_export(ms, cmd->args));
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		return (ms_pwd(ms));
	else if (!ft_strcmp(cmd->cmd, "unset"))
		return (ms_unset(ms, cmd->args));
	return (-1); // para debuguear
}
