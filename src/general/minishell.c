/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:11 by jenavarr          #+#    #+#             */
/*   Updated: 2024/01/24 18:05:15 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// testing una cosa
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
//

static int	ms_struct_init(t_ms *ms);
char	*get_home(void); // testing

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	argv[0] = NULL;
	argv = NULL;
	clearTerm(); // revisar
	if (argc > 1)
		return (ms_perror(ARGC_ERR, NULL, NULL, NULL));
/* 	int urandom_fd = open("/dev/urandom", O_RDONLY);
if (urandom_fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
}
if (dup2(urandom_fd, STDIN_FILENO) == -1) {
    perror("dup2");
    close(urandom_fd);
    exit(EXIT_FAILURE);
} */
	if (ms_struct_init(&ms) == FAILURE)
		return (FAILURE);
	if (env_list_init(&ms, envp) == FAILURE)
		return (FAILURE);
	disable_control_chars_echo();
	signal_handler(INTERACTIVE);
	if (readline_loop(&ms))
		return (FAILURE);
	restore_terminal_settings();
	exit(EXIT_SUCCESS);
	return (0);
}

static int	ms_struct_init(t_ms *ms)
{
	ms->pwd = getcwd(NULL, 0);
	if (!ms->pwd)
	{
		ms_perror(SHELL_INIT_ERROR, NULL, NULL, NULL);
		ms_perror(SH_MAKEPATH_ERROR, NULL, NULL, NULL);
		return (FAILURE);
	}
	ms->oldpwd = NULL;
	ms->home = get_home();
	ms->prevdir = NULL;
	ms->env = NULL;
	ms->token = NULL;
	ms->cmd = NULL;
	ms->num_cmd = 0;
	ms->envp = NULL;
	ms->shlvl = 0;
	ms->exit_status = 0;
	return (SUCCESS);
}

// Idea que he tenido, enseñar a Chus a ver qué piensa
char	*get_home(void)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		fstat;
	char			*home;

	dir = opendir("/Users");
	if (!dir)
		ms_quit("Opendir failure\n");
	entry = readdir(dir);
	while (entry != NULL)
	{
		home = ft_strjoin("/Users/", entry->d_name);
		if (!home)
			ms_quit(MALLOC_ERR);
		if (stat(home, &fstat) == -1)
			continue ;
		if ((fstat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) == 448 \
		&& ft_strcmp(home, "/Users/bocal") != 0)
			break ;
		free(home);
		entry = readdir(dir);
	}
	closedir(dir);
	return (home);
}
