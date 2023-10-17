/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:32:23 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/17 17:42:33 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Aquí pondré todo tipo de funciones que sean para debuguear cosas

/* Printea el puntero envp que el main ha recibido */
void	print_envp(char **envp)
{
	int	i;

	i = 0;
	printf("PRINT ENVP:\n");
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	// exit(EXIT_SUCCESS);
}

// // Printea los outputs de los builtin: env y export.
// void	print_env_and_export_output(t_ms *ms)
// {
// 	printf(">env\n");
// 	env_print(ms->env, ENV);
// 	printf("------------------------------------------------------------------\n");
// 	printf(">export\n");
// 	env_print(ms->env, EXPORT);
// 	exit (EXIT_SUCCESS);
// }

void	print_env(t_env *env)
{
	t_env *current;

	current = env;
	printf("PRINT ENV:\n");
	int i = 0;
	while (current)
	{
		printf("%s\n", current->name);
		i++;
		// printf("%s=", current->name);
		// printf("%s\n", current->content);
		current = current->next;
	}
	printf("TOTAL %d VARIABLES\n", i);
	// exit(EXIT_SUCCESS);
}

// Usa write para pritear un checkpoint rápidamente
void	check(void)
{
	static int	check_number;

	if (!check_number)
		check_number = 1;
	else
		check_number++;
	write(1, "CHECKPOINT ", 12);
	ft_putnbr(check_number);
	write(1, "\n", 1);
}
