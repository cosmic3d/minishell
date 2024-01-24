/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:08:42 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/24 16:38:07 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	export_print(t_env *env, t_env *abc_min, char *prev);
static int	argument_syntax(char *arg);
static void	print_error_export(char *arg);

int	ms_export(t_ms *ms, char **argv)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = SUCCESS;
	if (!argv[1])
		return (export_print(ms->env, NULL, NULL));
	if (ft_strcmp(argv[1], "--") == 0)
		i = 2;
	while (argv[i])
	{
		if (argument_syntax(argv[i]) == FAILURE)
		{
			print_error_export(argv[i]);
			exit_status = 1;
		}
		else if (process_argument(argv[i], ms) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (exit_status);
}

static int	export_print(t_env *env, t_env *abc_min, char *prev)
{
	t_env	*current;

	if (!env)
		return (SUCCESS);
	current = env;
	while (current)
	{
		if (!prev || ft_strcmp(current->name, prev) < 0)
		{
			if (!abc_min || ft_strcmp(current->name, abc_min->name) > 0)
				abc_min = current;
		}
		current = current->next;
	}
	if (abc_min)
	{
		export_print(env, NULL, abc_min->name);
		if (ft_strcmp(abc_min->name, "_") == 0)
			return (SUCCESS);
		printf("declare -x %s", abc_min->name);
		if (abc_min->content)
			printf("=\"%s\"", abc_min->content);
		printf("\n");
	}
	return (SUCCESS);
}

static int	argument_syntax(char *arg)
{
	int	i;

	if (arg[0] == '\0' || ft_isdigit(arg[0]))
		return (FAILURE);
	i = 0;
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (FAILURE);
		i++;
	}
	if (i == 0)
		return (FAILURE);
	if ((arg[i] == '+' && arg[i + 1] != '='))
		return (FAILURE);
	return (SUCCESS);
}

static void	print_error_export(char *arg)
{
	write(STDERR, "minishell: export: `", 20);
	write(STDERR, arg, ft_strlen(arg));
	write(STDERR, "\': not a valid identifier\n", 26);
	return ;
}
