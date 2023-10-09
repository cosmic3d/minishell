/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:11 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/09 18:47:08 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	// Declaramos struct general aquí?
	t_ms	ms;

	// Check para argc
	argv = NULL;
	if (argc != 1)
		return (ms_error(ARGC_ERR));

	// Clonamos envp
	// Esto va a ser MUCHO más complejo de lo que parecía por lo que he visto, pero POR AHORA
	// ms.env = ms_get_env(envp);
	ms.envp = ms_envp_dup(envp);
	if (!ms.envp)
		return (1);

	// Para Ctrl- 'D' 'C' '\'
	signal_handler();

	// Ahora llamamos a la función que en bucle usará readline y que es en definitiva el núcleo de minishell
	if (readline_loop())
		return (1);
	// Tenermos que acordar cual es el sistma que utilizamos para gestionar errores y la memoria
	// Usamos exit en vez de una cadena de returns?
	// Gestionamos los frees a palo seco? (óptimo)
	return (0); // default return del final de main
}

/* Este es el main con el que estuvimos testeando, 06-10-2023 */
// int	main(int argc, char **argv, char **envp)
// {
// 	int		i;
// 	char	*line;

// 	printf("%s %i\n", argv[0], argc);
// 	if (argc > 1)
// 		argv = NULL;
// 	i = -1;
// 	while (envp[++i])
// 		printf("%s\n", envp[i]);
// 	while (42)
// 	{
// 		line = readline("hola caracola");
// 		if (!line)
// 		{
// 			printf("Readline error\n");
// 			rl_clear_history();
// 			exit(1);
// 		}
// 		if (*line)
// 			add_history(line);
// 		if (!ft_strncmp(line, "exit", 4))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		free(line);
// 		//printf("%s", line);
// 	}
// 	rl_clear_history();
// 	return (0);
// }
