/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:11 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/06 17:34:24 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	*line;

	printf("%s %i\n", argv[0], argc);
	if (argc > 1)
		argv = NULL;
	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	while (42)
	{
		line = readline("hola caracola");
		if (!line)
		{
			printf("Readline error\n");
			rl_clear_history();
			exit(1);
		}
		if (*line)
			add_history(line);
		if (!ft_strncmp(line, "exit", 4))
		{
			free(line);
			break ;
		}
		free(line);
		//printf("%s", line);
	}
	rl_clear_history();
	return (0);
}
