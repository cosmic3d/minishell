/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:11 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/23 13:18:17 by apresas-         ###   ########.fr       */
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

	char	*print_arg[] = {"export", NULL};
	char	*set_zhola_arg[] = {"export", "ZHOLA=hola soy una variable", NULL};
	char	*unset_zhola_arg[] = {"unset", "ZHOLA", NULL};
	ms_export(&ms, set_zhola_arg);
	ms_export(&ms, print_arg);
	printf("\n");
	printf("\n");
	ms_unset(&ms, unset_zhola_arg);
	ms_export(&ms, print_arg);

	// exit(0);

	printf("PID = %d\n", getpid());

	// test_export(&ms);

	signal_handler();

	if (readline_loop(&ms))
		return (1);
	return (0);
}
