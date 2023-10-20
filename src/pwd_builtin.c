/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:54:04 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/20 17:56:36 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	// malloc check?
	write(1, &cwd, ft_strlen(cwd));
	free(cwd);
	return (EXIT_SUCCESS);
}
