/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:32:23 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/13 19:57:35 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Aquí pondré todo tipo de funciones que sean para debuguear cosas

/* Printea el puntero envp que el main ha recibido */
void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	exit(1);
}

// Printea los outputs de los builtin: env y export.
void	print_env_and_export_output(t_ms *ms)
{
	printf(">env\n");
	env_print(ms->env, ENV);
	printf("------------------------------------------------------------------\n");
	printf(">export\n");
	env_print(ms->env, EXPORT);
	exit (1);
}

void	print_env(t_env *env)
{
	t_env *current;

	current = env;
	while (current)
	{
		printf("name: %s\n", current->name);
		printf("content: %s\n", current->content);
		current = current->next;
	}
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

void	print_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		//printf("name: %s\n", current->type);
		printf("content: %s\n", current->content);
		current = current->next;
	}
}
