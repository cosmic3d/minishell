/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_brackets.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:26:27 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/18 18:26:27 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Si existen comillas comprueba si son válidas
int	valid_brackets(char *str)
{
	int		i;
	char	bracks;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			bracks = str[i++];
			while (42)
			{
				if (!str[i])
				{
					printf(BRACKS_ERROR, bracks);
					return (FALSE);
				}
				if (str[i] == bracks)
					break ;
				i++;
			}
		}
	}
	return (TRUE);
}

/*Elimina las parejas de brackets de un string, liberando del anterior y
devolviendo el nuevo sin brackets
En el caso de que no existan brackets en el string, devuelve el mismo.
ERRORES
Si hay algún error de syntaxis se imprime el mensaje de error y se devuelve NULL
Si hay algún error de malloc se sale del programa directamente*/
char	*erase_brackets(char *str)
{
	int		i;
	int		bracks_count;
	char	bracks;

	i = -1;
	bracks_count = 0;
	if (!valid_brackets(str))
	{
		free(str);
		return (NULL);
	}
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			bracks = str[i++];
			while (str[i] != bracks)
				i++;
			bracks_count += 2;
		}
	}
	if (!bracks_count)
		return (str);
	return (erase_brackets2(str, bracks_count));
}

/*Función auxiliar necesaria porque a norminette le sale de
los cojones*/
char	*erase_brackets2(char *str, int bracks_count)
{
	int		i;
	int		j;
	char	*new_str;
	char	bracks;

	i = -1;
	j = 0;
	new_str = (char *)ft_calloc(ft_strlen(str) - bracks_count + 1, sizeof(char));
	if (!new_str)
		exit(1); //Aquí llamaríamos a la función que libera todo y hace exit
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			bracks = str[i];
			while (str[++i] != bracks)
				new_str[j++] = str[i];
		}
		else
			new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}
