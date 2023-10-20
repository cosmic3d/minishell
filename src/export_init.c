/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:57:50 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/20 17:14:52 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_arg_syntax(t_export *data, char *arg);

void	export_init(t_export *data, char *arg)
{
	data->valid_name = 1;
	data->op = EXPORT_NO_OP;
	export_arg_syntax(data, arg);
	data->valid_content = data->op;
	data->name = NULL;
	data->content = NULL;
	if (!data->valid_name)
		data->exit_status = EXIT_FAILURE;
}

static void	export_arg_syntax(t_export *data, char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[i]))
		data->valid_name = 0;
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		if (!ft_isdigit(arg[i]) && !ft_isalpha(arg[i]) && arg[i] != '_')
			data->valid_name = 0;
		i++;
	}
	if ((arg[i] == '+' && arg[i + 1] != '=') || i == 0)
		data->valid_name = 0;
	if (!ft_strncmp(arg + i, "+=", 2))
		data->op = EXPORT_ADD;
	else if (!ft_strncmp(arg + i, "=", 1))
		data->op = EXPORT_EQ;
	data->eq_i = ft_strchr_i(arg, '=');
	data->name_len = i;
}

int	export_name_syntax(t_export *data, char *arg)
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
