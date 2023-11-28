/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:11 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/28 16:20:39 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	argv[0] = NULL;
	argv = NULL;
	if (argc != 1 || argv)
		return (ms_error(ARGC_ERR));

	// print_envp(envp); // debug
	// envp = NULL; // debug
	env_init(&ms, envp);

	char	*cdArg1[] = {"cd", "/Users/apresas-/Desktop/cd_tests/", NULL};
	ms_cd(&ms, cdArg1);

	ms_pwd(&ms);

	char	*cdArg2[] = {"cd", ".././../Dowloads", NULL};
	ms_cd(&ms, cdArg2);

	ms_pwd(&ms);

	char	*cdArg22[] = {"cd", ".././../Downloads", NULL};
	ms_cd(&ms, cdArg22);

	ms_pwd(&ms);

	char	*exportArg[] = {"./export", "PWD=\"Misco\"", NULL};
	ms_export(&ms, exportArg);

	char	*cdArg3[] = {"cd", "/Users/apresas-/Music/.././Pictures/././../utils/../minishell", NULL};
	ms_cd(&ms, cdArg3);

	ms_pwd(&ms);

	char	*cdArg4[] = {"cd", "minishell", NULL};
	ms_cd(&ms, cdArg4);

	ms_pwd(&ms);

	char	*echoArg1[] = {"echo", NULL};
	ms_echo(echoArg1);

	char	*echoArg2[] = {"echo", "hola que tal", "como estas", "miscoojones", "23", NULL};
	ms_echo(echoArg2);

	char	*echoArg3[] = {"echo", "-n", "-nnn", "-nnnnnn", "--n", "-n-n", "hola que tal", "como estas", "miscoojones", "23", NULL};
	ms_echo(echoArg3);

	ms_echo(echoArg1);

	char *echoArg4[] = {"echo", "-nnnnnnnnnnnnnnnnnnnn", "-n", "-nnnnnno", "holi", NULL};
	ms_echo(echoArg4);

	ms_echo(echoArg1);

	char	*echoArg5[] = {"echo", "-n", "-nnnnnnnnnnnnnnnnnnnnnnnnnn", NULL};
	ms_echo(echoArg5);

	// char *newpath[] = {"export", "PATH=tests", NULL};
	// ms_export(&ms, newpath);

	// char	*set_zhola_arg[] = {"export", "ZHOLA=hola soy una variable", "Z_NO=No_cal_más_tokens", "Z_SI=Si cal mas tokens", NULL};
	// char	*unset_zhola_arg[] = {"unset", "ZHOLA", NULL};
	// ms_export(&ms, set_zhola_arg);
	// char	*print_arg[] = {"export", NULL};
	// ms_export(&ms, print_arg);
	// printf("\n");
	// printf("\n");
	// ms_unset(&ms, unset_zhola_arg);
	// ms_export(&ms, print_arg);

	// exit(0);

	// printf("PID = %d\n", getpid());

	// test_export(&ms);
	disable_control_chars_echo();
	signal_handler();

	if (readline_loop(&ms))
		return (1);
	return (0);
}
