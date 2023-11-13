/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:27:34 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/13 17:44:42 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	possible_expansion(char *str);
// int	new_tokens_check(char *str, t_env *head);
// int	expand_check(char *str, t_env *head);
int	find_and_expand(t_ms *ms, t_token *token, char *str);

int	expansor(t_ms *ms, t_token *token)
{
	while (token)
	{
		if (token->type == TEXT) // Si el token es de tipo TEXT, usar el expansor
		{
			find_and_expand(ms, token, token->content);
			// printf("Might need new tokens? %d\n", new_tokens_check(token->content, ms->env));
		}
		token = token->next;
	}
	return (SUCCESS);
}

int	find_and_expand(t_ms *ms, t_token *token, char *str)
{
	token->can_expand = 1; // para que no se queje gcc
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		{
			printf("i = %d\n", i);
			str = update_token(ms, str, i);
			create_new_tokens(ms, token, str);
			// if (create_new_tokens(ms, token, str))
			// {
				
			// }
			// printf("token = %s\n", misco);
			// try_expand(ms, token, str, i);

		}
	}
	return (SUCCESS);
}

// int	try_expand(t_ms *ms, t_token *token, char *str, int i)
// {
// 	char	*var_name;
// 	int		len;

// 	len = 1;
// 	while (str[i + len])
// 	{
// 		if (!ft_isalnum(str[i]) && str[i] != '_')
// 			break;
// 		len++;
// 	}
// 	var_name = ft_strndup(str + i + 1, len);
// 	if (!var_name)
// 	{
// 		ms_error(MALLOC_ERR);
// 		exit(EXIT_FAILURE);
// 	}
// 	t_env *var;
// 	char *content;
// 	var = env_find(var_name, ms->env);
// 	if (!var)
// 	{
// 		// no existe la variable que buscabamos. Por lo tanto, la expansión se convierte a ""
// 		content = ft_strdup("");
// 		if (!content)
// 		{
// 			free(var_name);
// 			ms_error(MALLOC_ERR);
// 			exit(FAILURE);
// 		}
// 		// quizá puedo substituir esto por content = NULL y luego usar eso como check más adelante.
// 	}
// 	else
// 	{
// 		content = var->content;
// 	}
// 	join_contents();
// 	subtoken();
// }


/*
int	subtoken(char *str, int n, t_token *token)
{
	int	i;

	i = 0;
	1. recorremos str hasta n len (donde n es el indice del final de la expansión del token original)
	while (i < n)
	{
		// Si encontramos un separador de token, tenemos motivos para hacer un subtoken
		// creamos un token nuevo
		
			new_token->next = token
			new_token->prev = token->prev;
			token->prev->next = new_token;
			token->prev = token;

			new_token->content = ft_strndup(str, i) // siendo i el punto de separación del token
			// quitamos las comillas del nuevo token
			new_token->type = TEXT;
		// Ahora quitamos el content del new_token del content del token original
		aux = token->content;
		token->content = ft_substr(str, n, ft_strlen(str + n));
		// más o menos, la idea es esta
	}
}
*/

/*
Posible idea:
Que todo token tenga un int* con los index en los que se encuentran las quotes
Por ejemplo al tokenizar esto:
	"Esto es un 'token' "$VAR1" '$VAR2'"
	Entonces crearemos un int* con los valores 12, 18, 28, 34

La cantidad de single quotes es invariable. Todas las single quotes que aparezcan después de tokenizar son
inválidas. Por lo tanto, no tenemos que preocuparnos de tener que alojar nueva memoria. Lo único que tendremos
que hacer, es actualizar correctamente los valores de las single quotes después de cualquier expansión.

Cómo?

Cuando vayamos a expandir una variable, sabremos su longitud y su index. Si el index de la variable
a expandir es mayor que el index de una quote, esta quote no cambia de posición. Por que la expansión
ha sucedido más adelante en la string. Ejemplo:
	"'Hola' $VAR"
	Al expandir $VAR, la posición de las quotes de 'Hola' no cambia.
Si por el contrario, el índice de la expansión es inferior al de una quote, hay que cambiarla.

Necesitamos saber:
	index_quote
	index_origen_var
	var_name_len
	var_content_len

	ejemplo:

	"$VAR 'Hola'"
	(vamos a centrarnos en la primera quote antes del Hola')
	index_quote = 6
	index_origen_var = 1 (posición del $)
	var_name_len = 4 ($VAR)
	var_name_content = 5 (adios)

	Entonces, actualizamos el valor de index_quote así:

	new_index_quote = index_quote + (var_name_content - var_name_len);
	Es decir,
	index_quote += (5 - 4);
	Es decir,
	index_quote = 6 + 1 = 7.

	Y efectivamente podemos ver que tras expandir:

	"adios 'Hola'"

	El nuevo index de la quote es 7

	Con esta información, durante la expansión, si un single quote es encontrado, comprobaremos primero
	si su index es igual a algún valor de los index_quote de este token. Si lo es, significa que es
	una verdadera single quote con efecto especial. Si no lo es, entonces se trata de un caracter 
	literal y su efecto no se tendrá en cuenta.

	NOTA:

	Además de todo esto, CREO, que el expansor ni siquiera tiene que tener nada de esto en cuenta.
	El própio expansor irá expandiendo sobre la marcha.

	Podría quizá expandir, y sobre la marcha crear los nuevos tokens anteriores?

*/



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



*/
