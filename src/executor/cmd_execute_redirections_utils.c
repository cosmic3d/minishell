/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_redirections_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:44:18 by jenavarr          #+#    #+#             */
/*   Updated: 2023/12/21 21:28:45 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_mshtmp_str(char **result, int i)
{
	char	*tmp_str;

	tmp_str = ft_itoa(i);
	if (!tmp_str)
		ms_quit(MALLOC_ERR);
	free(*result);
	*result = ft_strjoin("/tmp/mshtmp_", tmp_str);
	if (!(*result))
	{
		free(tmp_str);
		ms_quit(MALLOC_ERR);
	}
	free(tmp_str);
	return (SUCCESS);
}
