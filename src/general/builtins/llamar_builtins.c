/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llamar_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:44:01 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/28 16:48:48 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// provisional
int	llamar_builtins(t_ms *ms)
{
	if (!ft_strcmp(ms->token->content, "exit"))
	{
		return (ms_exit(ms->cmd->args));
	}
	else if (!ft_strcmp(ms->cmd->args[0], "echo"))
	{
		return (ms_echo(ms->cmd->args));
	}
	else if (!ft_strcmp(ms->cmd->args[0], "env"))
	{
		return (ms_env(ms->env));
	}
	else if (!ft_strcmp(ms->cmd->args[0], "cd"))
	{
		return (ms_cd(ms, ms->cmd->args));
	}
	else if (!ft_strcmp(ms->cmd->args[0], "export"))
	{
		return (ms_export(ms, ms->cmd->args));
	}
	else if (!ft_strcmp(ms->cmd->args[0], "pwd"))
	{
		return (ms_pwd(ms));
	}
	else if (!ft_strcmp(ms->cmd->args[0], "unset"))
	{
		return (ms_unset(ms, ms->cmd->args));
	}
	return (0);	
}