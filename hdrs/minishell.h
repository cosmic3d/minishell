/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:05 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/20 18:33:47 by apresas-         ###   ########.fr       */
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
# include "../libs/libft/libft.h"
# include "../libs/readline/readline.h"
# include "../libs/readline/history.h"
# include <errno.h>

/* --------------------------------- MACROS --------------------------------- */

// signals
# define CTRL_C SIGINT
# define CTRL_BACKSLASH SIGQUIT

# define CMDPROMPT "minishell $ "
# define ENV 0
# define EXPORT 1

// Errors
# define MALLOC_ERR "Memory allocation failed.\n"
# define ARGC_ERR "Minishell does not accept arguments.\n"
# define GETCWD_ERR "The function getcwd() failed unexpectedly.\n"
# define READLINE_ERR "The function readline() failed unexpectedly.\n"
# define SHLVL_WARNING "minishell: warning: shell level (%d) too high,\
 resetting to 1\n"
# define CMD_ERROR "minishell: %s: command not found\n"
# define BRACKS_ERROR "minishell: unexpected EOF while looking for matching `%c\'\n"
# define SYNTAX_ERROR "minishell: syntax error near unexpected token `%s\'\n"

//Token types
# define TEXT 0
# define PIPE 1
# define REDIRECT_OUT 2
# define REDIRECT_APPEND 3
# define REDIRECT_IN 4
# define REDIRECT_HEARDOC 5

// Return status
# define SUCCESS 0
# define FAILURE 1
# define TRUE 1
# define FALSE 0

// Export valid character pattern
# define EXPORT_NAME_PATTERN "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstu\
vwxyz0123456789_"

// EXPORT OPERATORS
# define EXPORT_NO_OP 0
# define EXPORT_ADD 1
# define EXPORT_EQ 2

/* --------------------------------- STRUCTS -------------------------------- */

typedef struct s_env
{
	struct s_env	*prev;
	struct s_env	*next;
	char			*name;
	char			*content;
}				t_env;

typedef struct s_token
{
	struct s_token	*prev;
	struct s_token	*next;
	char			*content;
	int				type;
}				t_token;

typedef struct s_generic_list
{
	struct s_generic_list	*prev;
	struct s_generic_list	*next;
}				t_lst;

// typedef struct s_memory
// {
	// void	*ptr;
	// t_mem	*next;
// }				t_mem;

typedef struct s_minishell
{
	t_env	*env;
	t_token	*token;
	char	**envp;
	char	*prev_wd; // Previous working directory
	int		shlvl;
}				t_ms;

typedef struct s_export
{
	char	*name;
	char	*content;
	int		eq_i;
	int		name_len;
	int		op;
	int		valid_name;
	int		valid_content;
	int		exit_status;
}				t_export;

/* --------------------------------- FUNCS ---------------------------------- */

//////// DEBUG
void	print_envp(char **envp);
void	print_env_and_export_output(t_ms *ms);
void	print_env(t_env *env);
void	check(void);
void	test_export(t_ms *ms);
void	print_tokens(t_token *token);
//////////////

// env_builtin.c
int		env_print(t_env *env);

// env_list_init.c
void	env_init(t_ms *ms, char **envp);

// env_list_utils.c
int		env_add(char *name, char *content, t_env **head);
int		env_add_content(char *name, char *content, t_env *new);
t_env	*env_find(char *name, t_env *head);
int		env_remove(char *name, t_env *env);
int		env_update(char *name, char *content, t_env *env);
char	*get_env_content(char *name, t_env *env); // tendrá que ir a otro archivo más adelante

// error.c
int		ms_error(char *error_message);
void	export_perror(char *argument);

// export_init.c
void	export_init(t_export *data, char *arg);
int		export_name_syntax(t_export *data, char *arg);

// export_testing.c
int		ms_export(t_ms *ms, char **argv);
// int		export_print(t_env *env, t_env *current, t_env *abc_min, char *prev);

// generic list tools
void	*tail(void *node);
void	*head(void *node);
int		append(t_lst **head, size_t size); // ?????
void	swap(void *ptr_a, void *ptr_b); // TESTING

// prompt.c
// char	*set_prompt(char *cwd);

// readline_loop.c
int		readline_loop(t_ms *ms);
char	*terminal_entry(void);

// signal_handler.c
int		signal_handler(void);
void	disable_control_chars_echo(void);
void	restore_terminal_settings(void);

// utils.c
int		ms_arraylen(char **array);

//cmd_parse.c
int		tokenize(char *cmd_line, t_ms *ms);
int		get_token(int *i, char *cmd_line);
int		get_token_type(char *str);
void	add_token(char *cmd_line, int *i, int *nt, t_ms *ms);

//cmd_parse_brackets.c
int		valid_brackets(char *str);
char	*erase_brackets(char *str);
char	*erase_brackets2(char *str, int bracks_count);

//cmd_parse_checker.c
int		check_tokens(t_ms *ms);
int		check_token(t_token *token);

//token_list_utils.c
t_token	*token_tail(t_token *token);
void	free_tokens(t_token **token);
int		token_append(t_token **token);
int		in_x(char *str, char c);

#endif
