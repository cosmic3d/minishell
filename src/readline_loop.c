/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:52:54 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/09 18:21:31 by apresas-         ###   ########.fr       */
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
	char	*cwd;
	char	*prompt;
	char	*buffer;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ms_error_ptr(GETCWD_ERR));
	prompt = set_prompt(cwd);
	if (!prompt)
		return (NULL);
	buffer = readline(prompt);
	free(prompt);
	if (!buffer)
		return (ms_error_ptr(READLINE_ERR));
	if (buffer[0] != '\0')
		add_history(buffer);
	return (buffer);
}
