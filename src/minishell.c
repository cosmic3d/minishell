/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:11 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/13 18:45:04 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;
	int		i;
	char	*test;

	argv = NULL;
	if (argc != 1)
		return (ms_error(ARGC_ERR));

	// print_envp(envp); // debug
	// envp = NULL; // debug
	env_init(&ms, envp);

	signal_handler();

	if (readline_loop())
		return (1);
	return (0);
}
