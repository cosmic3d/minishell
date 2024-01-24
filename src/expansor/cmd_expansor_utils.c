/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansor_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:32:34 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/24 18:11:47 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		update_quote_positions(t_quotes *quote, t_var *var);
static t_var	*get_variable_data(t_ms *ms, char *str, int index);
char			*clear_spaces(char *str, t_quotes *q, t_var *var);

/* Expande y actualiza, si es posible, la variable de entorno indicada por 
str[*i], retorna la string resultante tras la expansión.
- Actualiza el valor de *i al final de la variable expandida.
- Llama a update_quote_positions() para updatear t_quotes *quote
- FALTA LIBERAR
*/
char	*expand_and_update(t_ms *ms, char *str, int *i, t_quotes *quote)
{
	t_var	*variable;
	char	*aux_str;
	char	*new_str;

	if (!ft_isalpha(str[*i + 1]) && str[*i + 1] != '_' && str[*i + 1] != '?')
		return (str);
	variable = get_variable_data(ms, str, *i);
	if (!variable->content)
		return (str);
	aux_str = ft_strljoin(str, *i, variable->content, -1);
	if (!aux_str)
		ms_quit(MALLOC_ERR);
	new_str = ft_strljoin(aux_str, -1, str + *i + variable->n_len + 1, -1);
	if (!new_str)
		ms_quit(MALLOC_ERR);
	free(aux_str);
	free(str);
	new_str = clear_spaces(new_str, quote, variable);
	update_quote_positions(quote, variable);
	*i += variable->c_len - 1;
	free(variable->name);
	free(variable->content);
	free(variable);
	return (new_str);
}

/* Limpia los espacios sobrantes a los bordes de la string tras una expansión */
char	*clear_spaces(char *str, t_quotes *q, t_var *var)
{
	char	*cleanstr;
	int		start;
	int		end;
	int		cleanlen;

	start = 0;
	end = ft_strlen(str) - 1;
	cleanstr = NULL;
	if (q->d_on == ON || end == -1)
		return (str);
	while (str[start] == ' ')
		start++;
	while (str[end] == ' ')
		end--;
	cleanlen = end - start + 1;
	if ((int)ft_strlen(str) == cleanlen)
		return (str);
	cleanstr = ft_strndup(str + start, cleanlen);
	if (!cleanstr)
		ms_quit(MALLOC_ERR);
	var->c_len = var->c_len - (ft_strlen(str) - ft_strlen(cleanstr));
	free(str);
	return (cleanstr);
}

/* Retorna un puntero a la struct s_variable_data inicializado y 
con la información sobre la variable indicada por str[index]. */
static t_var	*get_variable_data(t_ms *ms, char *str, int index)
{
	t_var	*var;

	str += index + 1;
	var = malloc(sizeof(t_var));
	if (!var)
		ms_quit(MALLOC_ERR);
	var->index = index;
	var->c_len = 0;
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
		if (quote->d[i] > var->index)
			quote->d[i] += var->c_len - var->n_len - 1;
		i++;
	}
	i = 0;
	while (quote->s[i] != -1)
	{
		if (quote->s[i] > var->index)
			quote->s[i] += var->c_len - var->n_len - 1;
		i++;
	}
	return ;
}
