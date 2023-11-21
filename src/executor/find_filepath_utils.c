/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_filepath_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:37:31 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/21 18:06:03 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Función de printeo de error para el executor, al menos durante los checks 
previos a la ejecución. */
int	exec_error(char *command, char *error_message)
{
	write(2, "minishell: ", 12);
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n", 1);
	return (FAILURE);
}

/* Comprueba si el archivo representado por cmd es un directorio */
int	is_directory(char *cmd)
{
	struct stat file;

	lstat(cmd, &file);
	if (S_ISDIR(file.st_mode))
		return (TRUE);
	return (FALSE);
}

/* Comprueba si el archivo representado por cmd es un archivo normal */
int	is_file(char *cmd)
{
	struct stat file;

	lstat(cmd, &file);
	if (S_ISREG(file.st_mode))
		return (TRUE);
	return (FALSE);
}

/* Libera un char **array */ // meter en libft?
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return ;
}

/* Une un nombre de archivo y el path a su directorio. */
char	*join_filename(char *filename, char *directory)
{
	char	*aux;
	char	*filepath;
	
	if (!filename || !directory)
		ms_quit("Fallo raro en join_filename"); // provisional
	aux = ft_strjoin(directory, "/");
	if (!aux)
		ms_quit(MALLOC_ERR);
	filepath = ft_strjoin(aux, filename);
	if (!filepath)
	{
		free(aux);
		ms_quit(MALLOC_ERR);
	}
	free(aux);
	return (filepath);
}
