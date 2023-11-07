/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:54:04 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/07 17:25:26 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* función que emula el funcionamiento del builtin pwd */
int	ms_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	// malloc check?
	write(1, &cwd, ft_strlen(cwd));
	free(cwd);
	return (EXIT_SUCCESS);
}
