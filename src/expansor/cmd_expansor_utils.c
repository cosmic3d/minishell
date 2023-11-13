/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansor_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:32:34 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/13 17:45:09 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Esta función recibe el contenido de un token como un puntero al caracter del 
mismo en el que se encuentre un $. Devuelve una string con el valor de la 
variable indicada tras ese $. Si la variable no existe, devuelve una string 
vacía. Si en algún momento algo falla, esta función termina el programa. */
static char	*variable_content(t_ms *ms, char *str)
{
	t_env	*var;
	char	*name;
	int		len;

	str++; // saltamos el '$'
	len = 0;
	if (str[0] == '?')
		return (NULL); // return (ft_itoa(ms->exit_status));
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	name = ft_strndup(str, len);
	if (!name)
		ms_quit(MALLOC_ERR);
	var = env_find(name, ms->env);
	if (!var) // si no se ha encontrado la variable, el content será ""
		return (ft_strdup(""));
	return (var->content);
}

char	*update_token(t_ms *ms, char *str, int j)
{
	// str = contenido del token
	// j = index donde se ha encontrado un $
	char	*aux_str;
	char	*new_str;
	char	*var_content;

	var_content = variable_content(ms, str + j);
	if (!var_content)
		ms_quit(MALLOC_ERR);
	printf("j = %d\n", j);
	aux_str = ft_strljoin(str, j, var_content, 0);
	if (!aux_str)
		ms_quit(MALLOC_ERR);
	printf("aux_str = %s\n", aux_str);
	j++;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	new_str = ft_strljoin(aux_str, 0, str + j, 0);
	if (!new_str)
		ms_quit(MALLOC_ERR);
	printf("new_str = %s\n", new_str);
	// free(str);
	return (new_str);
}

int	create_new_tokens(t_ms *ms, t_token *o_token, char *o_str)
{
	ms->shlvl = 1; // para que no llore gcc
	int	i;

	i = -1;
	while (o_str[++i])
	{
		if (o_str[i] == '"')
			i = ft_skip_chr_i(o_str, i);
		if (o_str[i] == ' ')
			printf("new token at i = %d\n", i);
	}
	return (0);
}

/*
	Names:

	$HOLA

	$___TAL

	$?

	$NOSEQUE123

	etc.

*/