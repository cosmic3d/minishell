/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:33:00 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/09 17:59:55 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// PROVISIONAL, printea el error_message al STDERR y retorna 1
int	ms_error(char *error_message)
{
	write(STDERR_FILENO, "Error\n", 7);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	return (1);
}

// PROVISIONAL TOO
void	*ms_error_ptr(char *error_message)
{
	write(STDERR_FILENO, "Error\n", 7);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	return (NULL);
}
