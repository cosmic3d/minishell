/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_coso2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:08:45 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/21 16:02:39 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define TYPE_CMD 1
#define TYPE_FILE 0

#define ERR_NO_SUCH_FILE 127
#define ERR_CMD_NOT_FOUND 127

#define NO_SUCH_FILE "No such file or directory"
#define CMD_NOT_FOUND "command not found"

t_ppath	*get_program(char *cmd, int *exit_status, t_ms *ms)
{
	t_ppath	*data;

	data = init_ppath_data(ms, cmd);
	if (!cmd || !cmd[0])
		return (no_cmd_case(ms, data));
	// data->exit_status = local_path_check(cmd); ya veremos
	if (!data->is_path && find_in_path(cmd, data, ms) == SUCCESS) // Es que ya tenemos el archivo encontrado sin fallos
		return (data);
	if (!data->is_path && find_in_pwd(cmd, data, ms) == SUCCESS) // Lo mismo
		return (data);
	if (find_as_absolute_path(cmd, data, ms) == SUCCESS) //
		return (data);

	return (data);
}


t_ppath	*init_ppath_data(t_ms *ms, char *cmd)
{
	t_ppath *data;

	data = malloc(sizeof(t_ppath));
	if (!data)
		ms_quit(MALLOC_ERR);
	data->filepath = NULL;
	data->error_message = NULL;
	data->exit_status = SUCCESS;
	data->path_exists = TRUE;
	data->envpath = env_find("PATH", ms->env);
	if (!data->envpath || !data->envpath->content || !data->envpath->content[0])
		data->path_exists = FALSE;
	data->cmd_type = TYPE_FILE;
	if (data->path_exists == FALSE)
		data->cmd_type = TYPE_CMD;
	data->is_path = FALSE;
	if (ft_strchr(cmd, '/'))
		data->is_path = TRUE;
	return (data);
}

t_ppath	*no_cmd_case(t_ms *ms, t_ppath *data)
{
	if (data->cmd_type == TYPE_FILE)
		data->exit_status = ERR_NO_SUCH_FILE;
	else if (data->cmd_type == TYPE_CMD)
		data->exit_status = ERR_CMD_NOT_FOUND;
	return (data);
}

int	find_in_path(char *cmd, t_ppath *data, t_ms *ms)
{
	char	**paths;
	char	*program;
	int		i;

	if (data->path_exists == FALSE)
		return (FAILURE);
	paths = ft_split(data->envpath, ':');
	i = 0;
	while (paths[i])
	{
		program = get_and_check_file(cmd, paths[i]);
	}
}

char	*get_and_check_file(char *filename, char *dir_path)
{
	char	*filepath;
	char	*aux;

	aux = ft_strjoin(dir_path, "/");
	if (!aux)
		ms_quit(MALLOC_ERR);
	filepath = ft_strjoin(aux, filename);
	if (!filepath)
		ms_quit(MALLOC_ERR);
	
	
}

#define _IS_DIR 126
#define IS_DIR "is a directory"
#define _PERMISSION_DENIED 126
#define PERMISSION_DENIED "Permission denied"
#define _NO_SUCH_FILE 127
#define NO_SUCH_FILE "No such file or directory"
#define _CMD_NOT_FOUND 127
#define CMD_NOT_FOUND "command not found"

char	*find_as_path(char *cmd, int *exit_status, t_ms *ms)
{
	if (access(cmd, F_OK) == SUCCESS) // el archivo EXISTE
	{
		if (is_directory(cmd))
		{
			*exit_status = _IS_DIR;
			exec_error(cmd, IS_DIR);
		}
		else if (is_file(cmd))
		{
			if (access(cmd, X_OK) == SUCCESS)
				return (cmd);
			*exit_status = _PERMISSION_DENIED;
			exec_error(cmd, PERMISSION_DENIED);
		}
		else
			exec_error(cmd, "Archivo raro?"); // provisional
	}
	else
	{
		*exit_status = ERR_NO_SUCH_FILE;
		exec_error(cmd, NO_SUCH_FILE);
	}
	return (NULL);
}


// Funciones que quizá hacen todo más leible aunque un poco menos eficiente
int	is_directory(char *cmd)
{
	struct stat file;

	lstat(cmd, &file);
	if (S_ISDIR(file.st_mode))
		return (TRUE);
	return (FALSE);
}

int	is_file(char *cmd)
{
	struct stat file;

	lstat(cmd, &file);
	if (S_ISREG(file.st_mode))
		return (TRUE);
	return (FALSE);
}

////////////////////////////////////////////////////////////////////////////////

char	*find_in_path(char *cmd, int *exit_status, t_ms *ms)
{
	char	*filepath;
	char	**path_dir;
	int		i;

	path_dir = get_path_directories(ms->env);
	if (!path_dir)
		return (NULL);
	i = 0;
	while (path_dir[i])
	{
		filepath = get_file_in_directory(cmd, exit_status, path_dir[i]);
		if (filepath || *exit_status != 0) // creo que todo bien pero dejo esto aquí de momento
		{
			free_array(path_dir);
			return (filepath);
		}
		i++;
	}
	free_array(path_dir);
	*exit_status = _CMD_NOT_FOUND;
	exec_error(cmd, CMD_NOT_FOUND);
	return (NULL);
}

char	**get_path_directories(t_env *env)
{
	t_env	*path_env;
	char	**path_split;

	path_env = env_find("PATH", env);
	if (!path_env || !path_env->content || !path_env->content[0])
		return (NULL);
	path_split = ft_split(path_env->content, ':');
	if (!path_split)
		ms_quit(MALLOC_ERR);
	return (path_split);
}

char	*get_file_in_directory(char *filename, int *exit_status, char *dir)
{
	char	*filepath;

	filepath = join_filename(filename, dir);
	if (access(filepath, F_OK) == SUCCESS) // si el archivo existe
	{
		if (is_file(filepath))
		{
			if (access(filepath, X_OK) == SUCCESS) // tiene permisos de ejecución
				return (filepath);
			*exit_status = _PERMISSION_DENIED;
			exec_error(filepath, PERMISSION_DENIED);
		}			
		else if (!is_directory(filepath))
			exec_error(filepath, "Archivo raro?"); // provisional
	}
	free(filepath);
	return (NULL);
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

char	*find_in_pwd(char *cmd, int *exit_status, t_ms *ms)
{
	char	*filepath;
	char	*pwd;

	pwd = exec_getcwd(cmd, exit_status);
	if (!pwd)
		return (NULL);
	filepath = join_filename(cmd, pwd);
	free(pwd);
	
	if (access(filepath, F_OK) == SUCCESS) // si el archivo existe
	{
		if (is_file(filepath))
		{
			if (access(filepath, X_OK) == SUCCESS)
				return (filepath);
			*exit_status = _PERMISSION_DENIED;
			exec_error(cmd, PERMISSION_DENIED);
		}
		else if (is_directory(filepath))
		{
			*exit_status = _IS_DIR;
			exec_error(cmd, IS_DIR);
		}
		else
			ms_quit("Archivo raro en pwd según el executor"); // provisional
	}
	else
	{
		*exit_status = _NO_SUCH_FILE;
		exec_error(cmd, NO_SUCH_FILE);
	}
	free(filepath);
	return (NULL);
}

char	*exec_getcwd(char *cmd, int *exit_status)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd) // han borrado el current directory de algún modo u otro
	{
		*exit_status = _NO_SUCH_FILE;
		exec_error(NO_SUCH_FILE);
		return (NULL);
	}
	return (cwd);
}

int	file_check(char *cmd, char *filename)
{
	if (access(filename, F_OK) == FAILURE)
	{
		exec_error(cmd, NO_SUCH_FILE);
		return (_NO_SUCH_FILE);
	}
	if (is_file(filename))
	{
		if (access(filename, X_OK) == FAILURE)
		{
			exec_error(cmd, PERMISSION_DENIED);
			return (_PERMISSION_DENIED);
		}
		return (SUCCESS);
	}
	else if (is_directory(filename))
	{
		exec_error(cmd, IS_DIR);
		return (_IS_DIR);
	}
	else
	{
		exec_error(cmd, "Archivo raro en exec, find");
	}
}

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