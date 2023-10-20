/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:57:50 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/19 20:14:39 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_get_op(char *arg);
static int	export_name_syntax(t_export *data, char *arg);

void	export_init(t_export *data, char *arg)
{
	data->valid_name = -export_name_syntax(data, arg);
	data->eq_i = ft_strchr_i(arg, '=');
	data->op = export_get_op(arg);
	data->valid_content = 1;
	if (data->op == EXPORT_NO_OP)
		data->valid_content = 0;
	data->name = NULL;
	data->content = NULL;
	return ;
}

static int	export_get_op(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
		i++;
	if (!ft_strncmp(arg + i, "+=", 2))
		return (EXPORT_ADD);
	else if (!ft_strncmp(arg + i, "=", 1))
		return (EXPORT_EQ);
	return (EXPORT_NO_OP);
}

static int	export_name_syntax(t_export *data, char *arg)
{
	int	return_status;
	int	i;

	i = 0;
	return_status = SUCCESS;
	if (arg[0] == '\0' || ft_isdigit(arg[0]))
		return_status = FAILURE;
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		if (!ft_match_ch(arg[i], EXPORT_NAME_PATTERN))
			return_status = FAILURE;
		i++;
	}
	if ((arg[i] == '+' && arg[i + 1] != '=') || i == 0)
		return_status = FAILURE;
	data->name_len = i;
	return (return_status);
}
