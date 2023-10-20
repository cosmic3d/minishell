/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:11 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/19 20:19:43 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;
	// int		i;
	// char	*test;

	argv[0] = NULL;
	argv = NULL;
	if (argc != 1)
		return (ms_error(ARGC_ERR));

	// print_envp(envp); // debug
	// envp = NULL; // debug
	env_init(&ms, envp);

	// print_envp(envp);
	// print_env(ms.env);

	char *argexport[] = { "export", NULL };
	ms_export(&ms, argexport);

	write(1, "\n\n\n", 3);

	char *argexportB[] = { "export", "ZHOOLA=miscojones", NULL };
	ms_export(&ms, argexportB);

	ms_export(&ms, argexport);

	exit(0);

	signal_handler();

	if (readline_loop())
		return (1);
	return (0);
}
