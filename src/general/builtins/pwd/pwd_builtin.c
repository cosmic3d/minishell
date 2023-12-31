/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:54:04 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/27 17:34:29 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* función que emula el funcionamiento del builtin pwd */
int	ms_pwd(t_ms *ms)
{
	write(1, ms->pwd, ft_strlen(ms->pwd));
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
