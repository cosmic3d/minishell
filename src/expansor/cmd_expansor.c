/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:27:34 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/09 18:34:30 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	possible_expansion(char *str);
int	new_tokens_check(char *str, t_env *head);
int	expand_check(char *str, t_env *head);

int	expansor(t_ms *ms, t_token *token)
{
	ms->shlvl = 1; // para que no se queje norminette por ahora
	while (token)
	{
		if (token->type == TEXT && possible_expansion(token->content))
		{
			// expand_token(ms, token);
			printf("Might need new tokens? %d\n", new_tokens_check(token->content, ms->env));
		}
		token = token->next;
	}
	return (SUCCESS);
}

/*

"$HOLA"$HOLA

echo holaecho hola
echo
holaecho
hola

"echo hola"echo hola

"$"


expansor:
1. comprueba que no haya comillas abiertas
2. comprueba comillas dobles
3. las quita y expande si es necesario | echo "$EXPAND"$EXPAND

EXPAND="hola"

"$EXPAND"$EXPAND

"hola ' hola"hola "'" hola


'$TAL'"$TAL"$TAL

int *iaray = [19, 23]

'$TAL'"$TAL"hola' hola

'$TAL'$TALhola' hola

'$TAL'hola' holahola' hola

$TALhola' holahola' hola



*/

int	expand_token(t_ms *ms, t_token *token)
{
	int	i;

	i = 0;
	while (token->content[i])
	{
		if (token->content[i] == '$' && can_expand_variable(token->content + i))
		{
			
		}
	}	
	
}

int	can_expand(char *str)
{
	str++;
	int	i;

	i = 0;
	if (str[i + 1] )
	while (str[i])
	{
		i++;
	}
}


int	expand_check(char *str, t_env *head)
{
	t_env	*var;
	char	*var_name;
	int		i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	var_name = malloc(sizeof(char) * (i + 1));
	if (!var_name)
	{
		ms_error(MALLOC_ERR);
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(var_name, str + 1, i);
	var = env_find(var_name, head);
	free(var_name);
	if (!var)
		return (FALSE);
	i = -1;
	while (var->content[++i])
	{
		if (ft_isspace(var->content[i]))
			return (TRUE);
	}
	return (FALSE);
}

int	new_tokens_check(char *str, t_env *head)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = ft_skip_chr_i(str, i);
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || \
		str[i + 1] == '?' || str[i + 1] == '_'))
		{
			return (expand_check(str + i, head));
		}
	}
	return (FALSE);
}

// Comprueba si este token debe ser expandido por el expansor
static int	possible_expansion(char *str)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\'')
			i = ft_skip_chr_i(str, i);
		else if (str[i] == '$' && \
		(ft_isalpha(str[i + 1]) || str[i + 1] == '?' || str[i + 1] == '_'))
			return (TRUE);
	}
	return (FALSE);
}


/* Lista de caracteres para los que $ no se intenta ni expandir
$ + CHAR
%
Nada
espacio
~
^
+
=
.
,
/
}
]
; ---> $; -> $ (sin el ;)

Nota: '\0' parece que sí lo intenta expandir

Hay que debatir qué hacemos al respecto. Cuando expandimos, cuando no, etc.

Mi propuesta, si no está formateado como una variable de entorno, no se expande nada.
*/

// char	*expand_to_string(t_ms *ms, char *old)
// {
// 	char	*new;
// 	int		i;

// 	i = -1;
// 	if (old[0] == '"'
// 	while (old[++i])
// 	{
// 		if (old[])
// 	}
// }

// char	*convert_token()

// char	**expand(t_ms *ms, t_token *token)
// {
// 	int		i;
// 	int		dquote;
// 	char	*content;

// 	i = -1;
// 	dquote = -1;
// 	content = token->content;
// 	while (content[++i])
// 	{
// 		if (content[i] == '"')
// 			dquote *= -1;
// 		if (content[i] == '\'')
// 			i = ft_skip_chr_i(content, i);
// 		else if (content[i] == '$' && (ft_isalpha(content[i + 1]) || \
// 		content[i + 1] == '?' || content[i + 1] == '_'))
// 		{
// 			if (dquote == 1) // Expandir sin hacer nuevos tokens
// 			{

// 			}
// 			else // Expandir con nuevos tokens
// 			{

// 			}
// 			/* Si lo que obtenemos dentro de la variable se puede traducir en varios tokens, se crean esos tokens,
// 			pero si todo esto se encontraba dentro de unas comillas dobles, entonces no se tiene que expandir en nuevos tokens.
// 			Es así?????
// 			*/
// 		}
// 	}
// }
