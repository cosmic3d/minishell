/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:52:17 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/24 16:30:15 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTINS_H
# define MINISHELL_BUILTINS_H

# include "minishell.h"

// Noseque
# define NUMERIC_ARG "numeric argument required"
# define TOO_MANY_ARG "too many arguments"

// CD Errors
# define NOT_DIR "Not a directory"
# define NO_SUCH_FILE "No such file or directory"
# define PERM_DENIED "Permission denied"
# define TOO_LONG "File name too long"
# define ERROR_RETRIEVE "error retrieving current directory: getcwd: cannot \
access parent directories"

// Long boundaries
# define LONG_MAX 9223372036854775807L
# define LMAX_10 922337203685477580L

// Export
int		process_argument(char *arg, t_ms *ms);
char	*get_name(char *arg);
char	*get_content(char *arg);
int		get_operation(char *arg);

// Cd
char	*set_dst(t_ms *ms, char **argv, int *flag);
char	*cd_oldpwd(t_ms *ms, int *flag);
char	*cd_home(t_ms *ms);

#endif