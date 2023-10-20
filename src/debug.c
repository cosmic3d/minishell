/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:32:23 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/20 18:37:19 by apresas-         ###   ########.fr       */
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

int	test_export_separados(t_ms *ms, int argc);
int test_export_juntos(t_ms *ms, int argc);
#include <unistd.h>

void	test_export(t_ms *ms)
{
	char	*arg_count_str;
	char	*option;

	arg_count_str = readline("Cuántos argumentos vas a introducir? ");
	int arg_count = ft_atoi(arg_count_str);
	free(arg_count_str);
	option = readline("Quieres testear los argumentos todos en un solo export \
	o separados? Escribe <j>untos> / <s>eparados> : ");
	if (!ft_strncmp(option, "juntos", 1))
		test_export_juntos(ms, arg_count);
	else if (!ft_strncmp(option, "separados", 1))
		test_export_separados(ms, arg_count);
	else
	{
		printf("Opción mal escrita\n");
		exit(1);
	}
	free(option);

	printf("Variables de entorno finales:\n");
	usleep(1000000);
	char *empty_arg[] = { "export", NULL};
	ms_export(ms, empty_arg);
	return ;
}

int test_export_juntos(t_ms *ms, int argc)
{
	char	**args;

	int i = 1;
	args = malloc(sizeof(char *) * (argc + 2));
	args[0] = ft_strdup("export");
	while (i < argc + 1)
	{	
		args[i] = readline("arg: ");
		
		i++;
	}
	args[i] = NULL;

	printf("\n");

	int exit_status = ms_export(ms, args);
	printf("exit_status = %d\n", exit_status);

	printf("\n\n");
	readline("Envía algún input para continuar");

	i = 0;
	while (i < argc)
	{
		free(args[i]);
		i++;
	}
	free(args);

	return (exit_status);
}

int	test_export_separados(t_ms *ms, int argc)
{
	char	***args;

	int	i = 0;
	args = malloc(sizeof(char **) * (argc));
	while (i < argc)
	{
		args[i] = malloc(sizeof(char *) * 3);
		args[i][0] = ft_strdup("export");
		args[i][1] = readline("arg: ");
		args[i][2] = NULL;

		i++;
	}

	i = 0;
	int *exit_status = malloc(sizeof(int) * (argc));
	while (i < argc)
	{
		exit_status[i] = ms_export(ms, args[i]);

		printf("\n----separador----\n");
		i++;
	}

	i = 0;
	printf("Todos los export han terminado\nResultados:\n");
	while (i < argc)
	{
		printf("Caso <%s> | exit_status = %d\n", args[i][1], exit_status[i]);
		i++;
	}


	i = 0;
	while (i < argc) {
		free(args[i][0]);
		free(args[i][1]);
		free(args[i]);
		i++; }
	free(args);
	return (0);
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
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
