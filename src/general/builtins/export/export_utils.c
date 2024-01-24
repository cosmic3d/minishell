/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:51:27 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/24 17:41:23 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_name(char *arg)
{
	char	*name;
	int		len;
	int		i;

	len = 0;
	while (arg[len] && arg[len] != '+' && arg[len] != '=')
		len++;
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
	{
		ms_perror("malloc", strerror(errno), NULL, NULL);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		name[i] = arg[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_content(char *arg)
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
		ms_quit(MALLOC_ERR);
	return (content);
}

int	get_operation(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=' && arg[i] != '+')
		i++;
	if (arg[i] == '+')
		return ('+');
	else if (arg[i] == '=')
		return ('=');
	else if (arg[i] == '\0')
		return (0);
	return (0);
}
