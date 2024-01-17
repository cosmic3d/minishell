/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_filepath_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:37:31 by apresas-          #+#    #+#             */
/*   Updated: 2024/01/17 19:42:01 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// OLD
// int	exec_error(char *command, char *error_message)
// {
// 	write(2, "minishell: ", 12);
// 	write(2, command, ft_strlen(command));
// 	write(2, ": ", 2);
// 	write(2, error_message, ft_strlen(error_message));
// 	write(2, "\n", 1);
// 	return (FAILURE);
// }

/* Función de printeo de error para el executor, al menos durante los checks
previos a la ejecución. */ //Chus: No sería mejor utilizar perror?
int	exec_error(char *cmd, char *error_str, int errnum)
{
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, error_str, ft_strlen(error_str));
	write(2, "\n", 1);
	return (errnum);
}

/* Devuelve TRUE o FALSE respecto al valor de check */
int	file_check(char *file_path, int check)
{
	struct stat	lfile;
	struct stat	file;

	if ((check == IS_FILE || check == IS_DIRECTORY || check == IS_LINK))
	{
		if (access(file_path, F_OK) != SUCCESS)
			return (FALSE);
		lstat(file_path, &lfile);
		stat(file_path, &file);
		if (check == IS_DIRECTORY && S_ISDIR(file.st_mode))
			return (TRUE);
		else if (check == IS_FILE && S_ISREG(file.st_mode))
			return (TRUE);
		else if (check == IS_LINK && S_ISLNK(file.st_mode))
			return (TRUE);
		return (FALSE);
	}
	else if (access(file_path, check) == SUCCESS)
		return (TRUE);
	return (FALSE);
}

// Versión 2 con flags, cute
// /* Devuelve TRUE o FALSE respecto al valor de check */
// int	file_check(char *file_path, int check)
// {
// 	struct stat	file;
// 	int	result;

// 	result = TRUE;
// 	if (access(file_path, F_OK) != SUCCESS)
// 		result = FALSE;
// 	else if (check & R_OK && access(file_path, R_OK) != SUCCESS)
// 		result = FALSE;
// 	else if (check & W_OK && access(file_path, W_OK) != SUCCESS)
// 		result = FALSE;
// 	else if (check & X_OK && access(file_path, X_OK) != SUCCESS)
// 		result = FALSE;
// 	lstat(file_path, &file);
// 	if (check & IS_DIRECTORY && !S_ISDIR(file.st_mode))
// 		result = FALSE;
// 	else if (check & IS_FILE && !S_ISREG(file.st_mode))
// 		result = FALSE;
// 	else if (check & IS_LINK && !S_ISLNK(file.st_mode))
// 		result = FALSE;
// 	return (result);
// }

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

char	*safe_getcwd(char *cmd, int *exit_status)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		*exit_status = exec_error(cmd, NO_SUCH_FILE, _NO_SUCH_FILE);
		return (NULL);
	}
	return (pwd);
}
