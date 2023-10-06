/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:01:47 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/06 15:09:07 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"

// Return value macros
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE 1

typedef struct s_simple_command
{
	char	**token;
	int		len;
	// ?
}				t_cmd;

typedef struct s_minishell
{
	t_cmd	*cmd_table;
	char	**env;
	int		env_len; // Maybe
}				t_ms;

#endif