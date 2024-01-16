/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansor_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:32:34 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/16 20:16:54 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		update_quote_positions(t_quotes *quote, t_var *var);
static t_var	*get_variable_data(t_ms *ms, char *str, int index);

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

	if (!ft_isalpha(str[*i + 1]) && str[*i + 1] != '_' && str[*i + 1] != '?' \
	&& str[*i + 1] != '\'' && str[*i + 1] != '"')
		return (str);
	// añadir ~ si queremos más adelante
	// Si hay comillas al inicio del nombre: al menos en mi casa:
	// - Ignorar ESAS comillas en particular y retornar:
	// $"VAR" ==> VAR
	// $'VAR' ==> VAR
	// $'V"AR' ==> V"AR
	// MENUDO COÑAZO
	variable = get_variable_data(ms, str, *i);
	aux_str = ft_strljoin(str, *i, variable->content, -1);
	if (!aux_str)
		ms_quit(MALLOC_ERR);
	new_str = ft_strljoin(aux_str, -1, str + *i + variable->n_len + 1, -1);
	if (!new_str)
		ms_quit(MALLOC_ERR);
	free(aux_str);
	free(str);
	update_quote_positions(quote, variable);
	*i += variable->c_len - 1;
	free(variable->name);
	free(variable->content);
	free(variable);
	return (new_str);
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
