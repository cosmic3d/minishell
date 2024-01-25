/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:05 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/20 20:05:29 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* --------------------------------- HEADERS -------------------------------- */
# define READLINE_LIBRARY

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <sys/stat.h>
# include <curses.h>
# include <dirent.h>
# include <sys/wait.h>
# include "../libs/libft/libft.h"
# include "../libs/readline/readline.h"
# include "../libs/readline/history.h"
# include <errno.h>
/* -------------------------------- GLOBAL -------------------------------- */
extern int	g_received_signal;
/* --------------------------------- MACROS --------------------------------- */

// signals
# define CTRL_C SIGINT
# define CTRL_BACKSLASH SIGQUIT

# define INTERACTIVE 0
# define HEREDOC 1

# define CMDPROMPT "minishell 🐌🐚 "
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
# define BRACKS_ERROR "minishell: unexpected EOF while \
looking for matching `%c\'\n"
# define SYNTAX_ERROR "minishell: syntax error near unexpected token `%s\'\n"
# define SHELL_INIT_ERROR "shell-init: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory"
# define SH_MAKEPATH_ERROR "sh_makepath: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory"
# define AMBIGUOUS_REDIRECT "minishell: ambiguous redirect"

//Token types
# define TEXT 0
# define PIPE 1
# define REDIRECT_OUT 2
# define REDIRECT_APPEND 3
# define REDIRECT_IN 4
# define REDIRECT_HEREDOC 5

// Return status
# define SUCCESS 0
# define FAILURE 1
# define TRUE 1
# define FALSE 0

// EXPORT OPERATORS
# define EXPORT_NO_OP 0
# define EXPORT_ADD 1
# define EXPORT_EQ 2

// Expansor
# define ON 1
# define OFF -1
# define SWITCH -1

// Executor filepath check errors
# define _IS_DIR 126
# define IS_DIR "is a directory"
# define _NOT_DIR 126
# define NOT_DIR "Not a directory"
# define _PERM_DENIED 126
# define PERM_DENIED "Permission denied"
# define _NO_SUCH_FILE 127
# define NO_SUCH_FILE "No such file or directory"
# define _CMD_NOT_FOUND 127
# define CMD_NOT_FOUND "command not found"
# define UNSUPPORTED_FILE "Specilal filetype not supported"

// For file_check
# define IS_FILE 8
# define IS_DIRECTORY 16
# define IS_LINK 32

// For open(), better readability of its macros
# define D_PERMS 0644
# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

/* --------------------------------- STRUCTS -------------------------------- */
typedef struct s_redirection
{
	int		type;
	char	*str;
	int		oflag;
}				t_redirection;

typedef struct s_cmdinfo
{
	char				*cmd;
	char				**args;
	t_redirection		*rd;
	int					num_rd;
	struct s_cmdinfo	*next_cmd;
	t_redirection		*rd_out;
	t_redirection		*rd_in;
	int					fdout;
	int					fdin;
	int					exists;
	int					rd_failed;
}				t_cmdinfo;

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
	struct s_quotes	*quotes;
	char			*content;
	int				type;
	int				hascontent; // testing
}				t_token;

typedef struct s_generic_list
{
	struct s_generic_list	*prev;
	struct s_generic_list	*next;
}				t_lst;

typedef struct s_memory
{
	struct s_memory	*prev;
	struct s_memory	*next;
	void			*ptr;
}				t_mem;

typedef struct s_minishell
{
	t_mem		*mem;
	t_env		*env;
	t_token		*token;
	t_cmdinfo	*cmd;
	char		*pwd;
	char		*oldpwd;
	char		*home;
	char		*prevdir;
	int			num_cmd;
	char		**envp;
	int			shlvl;
	int			forkret;
	int			exit_status;
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

typedef struct s_quotes
{
	int	*s;
	int	*d;
	int	s_on;
	int	d_on;
}				t_quotes;

typedef struct s_variable_data
{
	char	*name;
	char	*content;
	int		n_len;
	int		c_len;
	int		index;
}				t_var;

/* --------------------------------- FUNCS ---------------------------------- */

//////// DEBUG
void			print_envp(char **envp);
void			print_env_and_export_output(t_ms *ms);
void			print_env(t_env *env);
void			check(void);
void			test_export(t_ms *ms);
void			print_tokens(t_token *token);
void			print_cmd_structs(t_cmdinfo *cmdinfo, int num_cmd);
//////////////

////// Executor:
// cmd_env_creation.c
char			**env_list_to_envp(t_env *head);

// cmd_execute_redirections.c
int				iterate_rds(t_cmdinfo *cmd, int num_cmds, int *exit_status);
int				iterate_hrdcs(t_cmdinfo *cmd, int num_cmd, int *exit_status);

// cmd_execute_redirections_utils.c
int				get_mshtmp_str(char **result, int i);
int				do_hrdc_loop(int tmp_fd, char *tmp_str, char *tmp_eof, int *xs);
int				erase_hrdc_files(t_cmdinfo *cmd, int num_cmd);

// cmd_execute.c
int				execute_cmds(t_ms *ms);

// cmd_execute_utils.c
int				ms_dup(int fd, int fd2, int *newfd, int *xs);
int				ms_open(t_redirection *rd, int *fd, int *xs);
int				ms_pipe(int fd[2], int *xs);
int				ms_fork(int *forkret, int *xs);
int				set_exit_status(int forkret, int num_cmd);

// cmd_struct.c
void			free_cmd_structs(t_cmdinfo *cmdinfo, int cmd_num);
char			**get_arguments(t_token *token);
t_redirection	*get_redirections(t_token *token, int rd_count);
int				iterate_cmds(t_ms *ms);

// cmd_struct_utils.c
int				get_num_arguments(t_token *token);
int				get_num_redirections(t_token *token);
int				get_num_cmds(t_token *token);
void			get_rd_oflag(t_redirection *rd);

//// Get_pathname:
//find_filepath.c
char			*get_pathname(char *cmd, int *exit_status, t_ms *ms);

// find_filepath_utils.c
int				exec_error(char *cmd, char *error_str, int errnum);
int				file_check(char *file_path, int check);
char			*join_filename(char *filename, char *directory);
char			*safe_getcwd(char *cmd, int *exit_status);
char			*remove_slashes(char *str);

////// Expansor:
// cmd_expansor.c
int				expansor(t_ms *ms, t_token *token);

// cmd_expansor_utils.c
char			*update_token(t_ms *ms, char *str, int j);
char			*expand_and_update(t_ms *ms, char *str, int *i, t_quotes *q);

// cmd_home_expansor.c
char			*expand_home(t_ms *ms, char *str, int *i, t_quotes *quote);

// quotes_utils.c
int				is_valid_quote(int index, int *quote_array);
int				is_active_quote(char *str, int index, t_quotes *q);

// token_expansor.c
t_token			*retokenizer(t_token *token, t_ms *ms, t_token	*nt, char *tmp);
void			check_for_token_content(t_token *token);

// token_expansor_utils.c
int				*goodbrack(char bracks, t_token *t);
t_token			*token_joiner(char **strs);
char			*ms_substr(char *s, int start, int n, t_token *t);
void			token_traverse(t_token *t, int *i);

////// General:
// readline_loop.c
int				readline_loop(t_ms *ms);

//// Builtins:
// cd_builtin.c
int				ms_cd(t_ms *ms, char **argv);

// export_builtin.c
int				ms_export(t_ms *ms, char **argv);

// pwd_builtin.c
int				ms_pwd(t_ms *ms);

// echo_builtin.c
int				ms_echo(char **argv);

// exit_builtin.c
int				ms_exit(char **argv, int exit_status);

// env_builtin.c
int				ms_env(t_ms *ms);

// unset_builtin.c
int				ms_unset(t_ms *ms, char **argv);

// llamar_builtins.c
int				is_builtin(char *str);
int				exec_builtin(t_ms *ms, t_cmdinfo *cmd);

//// Lists:
// env_list_init.c
int				env_list_init(t_ms *ms, char **envp);

// env_list_utils.c
int				env_add(char *name, char *content, t_env **head);
t_env			*env_new(t_env **head);
int				env_edit(t_env *var, char *content);
void			env_remove(t_env *var);
void			env_free(t_ms *ms);

// env_list_utils_2.c
t_env			*env_find(char *name, t_env *head);
char			*get_env_content(char *name, t_env *env);

// generic_list_utils.c
void			*tail(void *node);
int				list_len(void *head);

// token_list_utils.c
t_token			*token_tail(t_token *token);
void			free_tokens(t_token **token);
void			free_token(t_token *tmp);
int				token_append(t_token **token);
int				in_x(char *str, char c);

//// Signals:
// echo_chars.c
void			disable_control_chars_echo(void);
void			restore_terminal_settings(void);

// signal_handler.c
int				signal_handler(int mode);

//// Utils
// error.c
int				ms_perror(char *s1, char *s2, char *s3, char *s4);
void			ms_quit(char *error_message);

// utils.c
int				ms_arraylen(char **array);
void			check_fds(void);
void			clearTerm(void);
int				reset_received_signal(void);

////// Parser:
//cmd_parse.c
int				tokenize(char *cmd_line, t_ms *ms);
int				get_token(int *i, char *cmd_line);
int				get_token_type(char *str);
void			add_token(char *cmd_line, int *i, int *nt, t_ms *ms);

//cmd_parse_brackets.c
int				valid_brackets(char *str);
char			*erase_brackets(char *str);
char			*erase_brackets2(char *str, int bracks_count);

//cmd_parse_checker.c
int				check_tokens(t_ms *ms);
int				check_token(t_token *token);
int				is_empty(char *str);

#endif
