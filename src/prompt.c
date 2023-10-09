/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:31:43 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/09 17:58:06 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_prompt(char *cwd)
{
	char	*prompt;
	char	*cdir;
	int		cdir_len;
	int		prefix_len;
	int		suffix_len;
	int		prompt_len;

	// Casos especiales:
	// Current directory = home
	// Current directory = /
	// Current directory = deleted directory .
	cdir = ft_strrchr(cwd, '/') + 1; // Usar ft_strrchr
	if (!cdir)
		return (ms_error_ptr("Provisional, ft_strrchr en set_prompt().\n"));
	/* Importante:
	ft_strrchr solo puede fallar si el caracter que se buscaba no estaba presente en la string enviada, o si la string enviada era nula.
	Cuando nuestro minishell esté listo. En teoría, ft_strrchr no deberia poder fallar nunca. Esto es algo a tener en cuenta. */
	cdir_len = ft_strlen(cdir);
	prefix_len = ft_strlen(PROMPT_PREFIX);
	suffix_len = ft_strlen(PROMPT_SUFFIX);
	prompt_len = cdir_len + prefix_len + suffix_len;
	prompt = malloc(sizeof(char) * (prompt_len + 1));
	if (!prompt)
		return (ms_error_ptr(MALLOC_ERR)); // Malloc error
	// printf debug, los dejo por si tengo problemas con esta función más adelante
	// printf("Before    strlcpy = %s\n", prompt);
	ft_strlcpy(prompt, PROMPT_PREFIX, prompt_len);
	// printf("After 1st strlcpy = %s\n", prompt);
	ft_strlcpy(prompt + prefix_len, cdir, prompt_len);
	// printf("After 2nd strlcpy = %s\n", prompt);
	ft_strlcpy(prompt + prefix_len + cdir_len, PROMPT_SUFFIX, prompt_len);
	// printf("After 3rd strlcpy = %s\n", prompt);
	prompt[prompt_len + 1] = '\0';
	return (prompt);
}
