/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:11 by jenavarr          #+#    #+#             */
/*   Updated: 2023/11/23 18:07:30 by jenavarr         ###   ########.fr       */
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
