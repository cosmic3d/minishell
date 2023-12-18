/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:57:02 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/18 16:52:02 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_verify_name(char *arg);
static int	unset_error(char *argument);

/* función que emula el builtin unset */
int	ms_unset(t_ms *ms, char **argv)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = EXIT_SUCCESS;
	while (argv[i])
	{
		if (unset_verify_name(argv[i]) == SUCCESS)
			env_remove(env_find(argv[i], ms->env));
		else
			exit_status = unset_error(argv[i]);
		i++;
	}
	return (exit_status);
}

/* Retorna 0 si el argumento proporcionado sigue el syntax de una variable de 
entorno, retorna 1 en caso contrario */
static int	unset_verify_name(char *arg)
{
	int		i;

	i = 0;
	if (ft_isdigit(arg[0]))
		return (FAILURE);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (FAILURE);
		i++;
	}
	if (i == 0)
		return (FAILURE);
	return (SUCCESS);
}

/* Printea el mensaje de error de unset "not a valid identifier" siguiendo el 
formato apropiado. */
static int	unset_error(char *argument)
{
	write(STDERR, "minishell: unset: `", 19);
	write(STDERR, argument, ft_strlen(argument));
	write(STDERR, "\': not a valid identifier\n", 26);
	return (EXIT_FAILURE);
}
