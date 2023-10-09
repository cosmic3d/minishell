/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:52:54 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/09 18:52:22 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prototipo provisional // Nombre provisional
int	readline_loop(void)
{
	char	*buffer;

	while (42)
	{
		buffer = terminal_entry();
		if (!buffer)
			return (1);
		// Aquí enviaríamos el buffer al parser
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
		if (rl_eof_found == 1)
			printf("EOF FOUND\n");
		else
			printf("Misco\n");
		// ms_error(READLINE_ERR);
		return (NULL);
	}
	if (buffer[0] != '\0')
		add_history(buffer);
	return (buffer);
}
