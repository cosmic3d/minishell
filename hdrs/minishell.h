/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:05 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/10 18:27:37 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* --------------------------------- HEADERS -------------------------------- */
# define READLINE_LIBRARY

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <sys/stat.h>
# include <curses.h>
# include "../libs/readline/readline.h"
# include "../libs/readline/history.h"
# include "../libs/ft_libft/libft.h"
# include <errno.h>

/* --------------------------------- MACROS --------------------------------- */

// signals
# define CTRL_C SIGINT
# define CTRL_BACKSLASH SIGQUIT

# define CMDPROMPT "minishell $ "

// Errors
# define MALLOC_ERR "Memory allocation failed.\n"
# define ARGC_ERR "Minishell does not accept arguments.\n"
# define GETCWD_ERR "The function getcwd() failed unexpectedly.\n"
# define READLINE_ERR "The function readline() failed unexpectedly.\n"
# define SHLVL_WARNING "minishell: warning: shell level (%d) too high,\
 resetting to 1\n"
/* --------------------------------- STRUCTS -------------------------------- */

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*name;
	char			*content;
}				t_env;

// typedef struct s_memory
// {
	// void	*ptr;
	// t_mem	*next;
// }				t_mem;

typedef struct s_minishell
{
	t_env	*env;
	char	**envp;
	char	*prev_wd; // Previous working directory
	int		shlvl;
}				t_ms;

/* --------------------------------- FUNCS ---------------------------------- */

// env_list.c
t_env	*env_list(char **og_envp);
t_env	*env_new_node(void);
void	env_add_node(t_env **tail, t_env *new);

// env_shlvl.c

// env.c
t_env	*env_init(char **envp);
int		env_shlvl(t_env *head);
int		env_update_shlvl(t_env *env);


// error.c
int		ms_error(char *error_message);
void	*ms_error_ptr(char *error_message);

// prompt.c
// char	*set_prompt(char *cwd);

// readline_loop.c
int		readline_loop(void);
char	*terminal_entry(void);

// signal_handler.c
int		signal_handler(void);

// utils.c
int		ms_arraylen(char **array);

#endif
