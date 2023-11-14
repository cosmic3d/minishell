/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansor_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:32:34 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/14 19:15:51 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		update_quote_positions(t_quotes *quote, t_var *var);
static t_var	*get_variable_data(t_ms *ms, char *str, int index);

/* Esta función recibe un puntero *str al contenido de un token, también 
recibe j que es el indice en el que en str podemos encontrar un '$', indicando 
que podría haber una variable a expandir.
Esta función expande, si es posible, la variable indicada por el '$' y devuelve 
la string actualizada. */
char	*expand_and_update(t_ms *ms, char *str, int *i, t_quotes *quote)
{
	t_var	*variable;
	char	*aux_str;
	char	*new_str;
	
	if (!ft_isalpha(str[*i + 1]) && str[*i + 1] != '_' && str[*i + 1] != '?')
		return (str);
	variable = get_variable_data(ms, str + *i + 1, *i);
	aux_str = ft_strljoin(str, *i, variable->content, -1);
	if (!aux_str)
		ms_quit(MALLOC_ERR);
	new_str = ft_strljoin(aux_str, -1, str + *i + variable->n_len + 1, -1);
	if (!new_str)
		ms_quit(MALLOC_ERR);
	update_quote_positions(quote, variable);
	*i += variable->c_len - 1;
	free(aux_str);
	free(str);
	return (new_str);
}

/* Esta función retorna un puntero a la struct s_variable_data inicializado y 
con la información sobre la variable a la que apunta el puntero str.
str ha de ser un puntero al primer caracter del nombre de una variable. 
index ha de ser el index en la string del token equivalente al $ que precede 
el nombre de la variable. */
static t_var	*get_variable_data(t_ms *ms, char *str, int index)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		ms_quit(MALLOC_ERR);
	var->n_len = 0;
	if (str[0] == '?')
		var->n_len = 1;
	while (ft_isalnum(str[var->n_len]) || str[var->n_len] == '_')
		var->n_len++;
	var->name = ft_strndup(str, var->n_len);
	if (!var->name)
		ms_quit(MALLOC_ERR);
	if (var->name[0] == '?')
		var->content = ft_itoa(ms->exit_status);
	else
		var->content = get_env_content(var->name, ms->env);
	if (!var->content)
		ms_quit(MALLOC_ERR);
	var->c_len = ft_strlen(var->content);
	var->index = index;
	return (var);
}

/* Actualiza los valores de la struct t_quotes recibida en base la expansión de 
la variable var en el token cuyo contenido es str. */
static void	update_quote_positions(t_quotes *quote, t_var *var)
{
	int	i;

	i = 0;
	while (quote->d[i] != -1)
	{
		// printf("old quote [%d] = %d\n", i, quote->d[i]); // debug
		if (quote->d[i] > var->index)
			quote->d[i] += ft_abs(var->c_len - var->n_len) - 1;
		// printf("new quote [%d] = %d\n", i, quote->d[i]); // debug
		i++;
	}
	i = 0;
	while (quote->s[i] != -1)
	{
		if (quote->s[i] > var->index)
			quote->s[i] += ft_abs(var->c_len - var->n_len) - 1;
		i++;
	}
	return ;
}

// int	create_new_tokens(t_ms *ms, t_token *o_token, char *o_str)
// {
// 	ms->shlvl = 1; // para que no llore gcc
// 	int	i;

// 	i = -1;
// 	while (o_str[++i])
// 	{
// 		if (o_str[i] == '"')
// 			i = ft_skip_chr_i(o_str, i);
// 		if (o_str[i] == ' ')
// 			printf("new token at i = %d\n", i);
// 	}
// 	return (0);
// }
