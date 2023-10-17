/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:52:54 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/17 18:32:20 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prototipo provisional // Nombre provisional
int	readline_loop(t_ms *ms)
{
	char	*buffer;

	while (42)
	{
		buffer = terminal_entry();
		if (!buffer)
			return (1);
		tokenize(buffer, ms);
		//exit(1);
		print_tokens(ms->token);
		free_tokens(&ms->token);
		free(buffer);
	}
	rl_clear_history();
	return (0);
}

// Prototipo provisional // Nombre provisional
char	*terminal_entry(void)
{
	char	*buffer;

	buffer = readline(CMDPROMPT);
	if (!buffer)
	{
		// Una de dos:
		// Error de readline
		// NULL enviado a readline
		return (NULL);
	}
	if (buffer[0] != '\0')
		add_history(buffer);
	return (buffer);
}
