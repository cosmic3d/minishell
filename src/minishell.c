/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:11 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/20 18:40:11 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	argv[0] = NULL;
	argv = NULL;
	if (argc != 1)
		return (ms_error(ARGC_ERR));

	// print_envp(envp); // debug
	// envp = NULL; // debug
	env_init(&ms, envp);

	// test_export(&ms);

	signal_handler();

	if (readline_loop(&ms))
		return (1);
	return (0);
}
