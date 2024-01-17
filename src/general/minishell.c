/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:39:11 by jenavarr          #+#    #+#             */
/*   Updated: 2024/01/17 19:56:35 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_struct_init(t_ms *ms);

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	argv[0] = NULL;
	argv = NULL;
	clearTerm();
	if (argc == 0) // debug
		exit(1); // 
	// if (argc > 1 || !isatty(STDIN))
		// return (ms_perror(ARGC_ERR, NULL, NULL, NULL));
	if (ms_struct_init(&ms) == FAILURE)
		return (FAILURE);
	if (env_list_init(&ms, envp) == FAILURE)
		return (FAILURE);
	// env_free(&ms);// debug
	// free(ms.pwd);
	// return (0);//
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
	// si añado ms->mem hay que ponerlo a NULL
	ms->pwd = getcwd(NULL, 0);
	if (!ms->pwd) // antes if (errno)
	{
		ms_perror("getcwd", strerror(errno), NULL, NULL);
		return (FAILURE);
	}
	ms->env = NULL;
	ms->token = NULL;
	ms->cmd = NULL;
	ms->num_cmd = 0;
	ms->envp = NULL;
	ms->shlvl = 0;
	ms->exit_status = 0;
	return (SUCCESS);
}

// void	*ms_malloc(size_t size, t_ms *ms)
// {
// 	void	*memory;

// 	memory = malloc(size);
// 	if (!memory)
// 	{
// 		ms_perror("malloc", strerror(errno), NULL, NULL);
// 		return (NULL);
// 	}
// 	if (add_mem(memory, &ms->mem) == FAILURE)
// 	{
// 		free(memory);
// 		return (NULL);
// 	}
// 	return (memory);
// }

// int	add_mem(void *ptr, t_mem **mem)
// {
// 	t_mem	*new;
// 	t_mem	*last;

// 	new = malloc(sizeof(t_mem));
// 	if (!new)
// 	{
// 		ms_perror("malloc", strerror(errno), NULL, NULL);
// 		return (FAILURE);
// 	}
// 	new->prev = NULL;
// 	new->next = NULL;
// 	if (*mem == NULL)
// 		*mem = new;
// 	else
// 	{
// 		last = tail(*mem);
// 		last->next = new;
// 		new->prev = last;
// 	}
// 	return (SUCCESS);
// }

// void	rm_mem(void *rm, t_mem **mem)
// {
// 	t_mem	*current;

// 	if (!rm)
// 		return ;
// 	current = *mem;
// 	while (current)
// 	{
// 		if (current->ptr == rm)
// 		{
// 			if (current->prev)
// 				current->prev->next = current->next;
// 			if (current->next)
// 				current->next->prev = current->prev;
// 			free(current->ptr);
// 			free(current);
// 		}
// 		current = current->next;
// 	}
// 	return ;
// }
