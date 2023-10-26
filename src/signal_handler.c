/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:01:55 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/26 20:13:20 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

// provisional
int	signal_handler(void)
{
	signal(CTRL_C, signal_tal);
	signal(CTRL_BACKSLASH, signal_tal);
	return (1);
}
