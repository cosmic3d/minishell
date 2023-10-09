/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:01:55 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/09 18:29:41 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// provisional
static void	signal_tal(int signum)
{
	if (signum == CTRL_C)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == CTRL_BACKSLASH)
		return ;
	// else if (signum == CTRL_D)
	// {
	// 	// }
	// Aparentemente Ctrl-D no funciona igual que los demás
	// Quizá hay que modificar el comportamiento del readline_loop para
	// gestionarlo
}

// provisional
int	signal_handler(void)
{
	signal(CTRL_C, signal_tal);
	signal(CTRL_BACKSLASH, signal_tal);
	return (1);
}


