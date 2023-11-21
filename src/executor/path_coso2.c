/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_coso2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:08:45 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/21 17:56:27 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////////////////////////////////////////////////////////////////////////////////

// Descartado
// char	*special_path_case(char *filename, int *exit_status, char *dir)
// {
// 	char	*cmd;
// 	char	*filepath;

// 	cmd = join_filename(dir, filename);
// 	filepath = join_filename(".", cmd);
// 	if ()
// }

// OLD
// char	*exec_getcwd(char *cmd, int *exit_status)
// {
// 	char	*cwd;

// 	cwd = getcwd(NULL, 0);
// 	if (!cwd) // han borrado el current directory de algún modo u otro
// 	{
// 		*exit_status = _NO_SUCH_FILE;
// 		exec_error(NO_SUCH_FILE);
// 		return (NULL);
// 	}
// 	return (cwd);
// }

// OLD
// int	file_check(char *cmd, char *filename)
// {
// 	if (access(filename, F_OK) == FAILURE)
// 	{
// 		exec_error(cmd, NO_SUCH_FILE);
// 		return (_NO_SUCH_FILE);
// 	}
// 	if (is_file(filename))
// 	{
// 		if (access(filename, X_OK) == FAILURE)
// 		{
// 			exec_error(cmd, PERMISSION_DENIED);
// 			return (_PERMISSION_DENIED);
// 		}
// 		return (SUCCESS);
// 	}
// 	else if (is_directory(filename))
// 	{
// 		exec_error(cmd, IS_DIR);
// 		return (_IS_DIR);
// 	}
// 	else
// 	{
// 		exec_error(cmd, "Archivo raro en exec, find");
// 	}
// }

// int	local_path_check(t_ppath *data, char *cmd)
// {
// 	struct stat info;
// 	int			i;

// 	lstat(cmd, &info);
// 	if (!S_ISREG(info.st_mode))
// 	{
// 		i = -1;
// 		while (cmd[++i])
// 		{
// 			if (cmd[i] == '/')
// 			{
// 				if (access(cmd, F_OK) == SUCCESS)
// 				{
// 					data->exit_status = ERR_IS_DIR;
// 					break ;
// 				}
// 				data->exit_status = ERR_NO_SUCH_FILE;
// 				break ;
// 			}
// 		}
// 	}
// 	else if (S_ISDIR(info.st_mode))
// 	{
// 		data->exit_status = ERR_CMD_NOT_FOUND;
// 	}
// 	return (data);
// }

/* Explicación de cómo entiendo que funciona esta función:

Primero, hacemos lstat y tenemos la info del archivo cmd.

Si cmd está formateado como un directorio puede que lo sea, o puede que solo lo parezca.

Por ello, hacemos if !regular (Si el archivo no es un archivo normal y corriente)

busca cmd[i] == '/'

Si lo encuentras, entonces sabremos que puede que sea un directorio.
Intentamos acceder a él con access.
Si F_OK da bien, es que el archivo existe y como sabemos que no es un archivo normal gracias a !regular, entonces es un directorio.

Pero no solo eso, ahora vemos que tenemos un directorio como comando de nuestro command line, por lo tanto, eso es un error ERR_IS_DIR

En caso de haber '/' pero no poder abrirlo con access, entonces sabemos que NO puede ser un archivo por que los archivos no pueden 
contener el caracter '/', además no puede ser un directorio por que access no ha podido encontrarlo. Por lo tanto, es un error de tipo
No such file or directory / Command not found


Si en ~ hago:
>Downloads

Me dice "command not found" (127)

Si hago unset de PATH o hago que PATH=""
>Downloads

Me dice "is a directory" (126)

*/
// int	directory_check(char *cmd, t_ppath *data)
// {
// 	struct stat	info;
// 	int			i;
// 	int			is_regular;

// 	lstat(cmd, &info);
// 	i = 0;
// 	is_regular = S_ISREG(info.st_mode);
// 	while (cmd[i] && !is_regular)
// 	{
// 		if (cmd[i] == '/')
// 		{
// 			if (access(cmd, F_OK) == SUCCESS)
// 				return (ERR_IS_DIR);
// 			else
// 				return (ERR_NO_SUCH_FILE); // Lo podriamos gestionar diferente?
// 		}
// 	}
// 	if (S_ISDIR(info.st_mode))
// }