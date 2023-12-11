/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:51:27 by apresas-          #+#    #+#             */
/*   Updated: 2023/12/11 17:04:35 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_equal(t_env *var, char *arg);
int	export_add(t_env *var, char *arg);
int	export_new(char *name, char *arg, t_ms *ms);
int	get_operation(char *arg);

static char	*get_content(char *arg)
{
	char	*content;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '\0')
		return (NULL);
	i++;
	content = ft_substr(arg, i, ft_strlen(arg + i));
	if (!content)
	{
		ms_perror("malloc", strerror(errno), NULL, NULL);
		return (NULL);
	}
	return (content);
}

