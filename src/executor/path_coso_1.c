/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_coso_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:15:36 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/21 17:58:21 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define FILE_NO_ACCESS 126
#define FILE_NOT_FOUND 127

#define TYPE_FILEDIR 1
#define TYPE_CMD 0

// char	*find_program(char *name, int *exit_status, t_ms *ms)
// {
// 	char	*filepath;
// 	int		type;
// 	int		check;
	
// 	filepath = name;
// 	if (ft_strchr(name, '/') == FOUND)
// 		type = TYPE_FILEDIR;
// 	else
// 		filepath = find_in_path(name, &type, ms);
// 	check = check_permissions(filepath);
//  	if (check != SUCCESS)
// 		*exit_status = check;
// }

// /* Retorna el numero de error apropiado en caso de que el archivo al que 
// queramos acceder no tenga los permisos necesarios o no exista. */
// int	check_permissions(char *filepath)
// {
// 	if (access(filepath, F_OK) == SUCCESS)
// 	{
// 		if (access(filepath, X_OK) == SUCCESS)
// 			return (SUCCESS);
// 		else
// 			return (FILE_NO_ACCESS);
// 	}
// 	return (FILE_NOT_FOUND);
// }

// char	*find_in_path(char *name, int *exit_status, t_ms *ms)
// {
// 	char	*program;
// 	char	**path;
// 	int		i;

// 	path = get_paths(ms->env, exit_status);
// 	if (!path)
// 		return (NULL);
// 	i = -1;
// 	while (path[++i])
// 	{
// 		program = get_file_in_directory(name, path[i]);
// 		if (program)
// 			break ;
// 	}
// 	i = -1;
// 	while (path[++i])
// 		free(path[i]);
// 	free(path);
// 	if (!program)
// 	{
// 		*exit_status = ERR_CMD_NOT_FOUND;
// 		return (NULL);
// 	}
// 	return (program);
// }

// char	**get_paths(t_env *env, int *exit_status)
// {
// 	t_env	*path_env;
// 	char	**path_split;

// 	path_env = env_find("PATH", env);
// 	if (!path_env || !path_env->content[0])
// 	{
// 		*exit_status = ERR_NO_SUCH_FILE;	
// 		return (NULL);
// 	}
// 	path_split = ft_split(path_env->content, ':');
// 	if (!path_split)
// 		ms_quit(MALLOC_ERR);
// 	// aquí haré algunas pruebas por si acaso, printear el contenido y eso, pero en teoría está bien
// 	return (path_split);
// }

// /* Busca el archivo de nombre filename en el directorio dir_path. 
// Si lo encuentra, retorna el dir_path concatenado con el filename. Si no lo 
// encuentra, retorna NULL. */
// char	*get_file_in_directory(char *filename, char *dir_path)
// {
// 	char	*filepath;
// 	char	*aux;

// 	aux = ft_strjoin(dir_path, "/");
// 	if (!aux)
// 		ms_quit(MALLOC_ERR);
// 	filepath = ft_strjoin(aux, filename);
// 	if (!filepath)
// 		ms_quit(MALLOC_ERR);
// 	free(aux);
// 	if (access(filepath, F_OK) == SUCCESS)
// 	{
// 		if (access(filepath, X_OK) == SUCCESS)
// 			return (filepath);
// 		exit_status = ERR_NO_ACCESS;
// 			return (NULL);
// 	}
// 	else
// 	{
// 		free(filepath);
// 		return (NULL);
// 	}
// }


// /* Cuando bash comprueba el comando a buscar en el path o no, puede interpretarlo de dos formas:

// un File / Directory o un Command.

// Si el archivo tiene un formato de directorio, como por ejemplo "path/to/file"
// bash lo tratará como un "file/directory"

// Pero si se trata de solo una palabra, bash lo tratará como un Command, por ejemplo "ls"

// Sin embargo, PATH no existe, o PATH="", entonces bash sabrá que no hay nada que buscar
// en PATH, así que lo tratará todo como "file/directory".

// QUÉ IMPORTANCIA TIENE?

// Pues que si hacemos, por ejemplo:

// ./ls, bash dirá "Esto es un file/directory", y al darse cuenta de que no existe, dirá:

// "No such file or directory"

// Pero si a bash le pasamos "ls", pensará "Esto es un command" y en caso de no encontrarlo en path, dirá:

// "Command not found"

// También hay la posibilidad de que el comando que bash quiera ejecutar sea un directorio y el error
// dirá:
// "is a directory"
// */

// /* Orden de checks de bash:

// 1. En un path indicado por PATH, en orden de aparición
// 2. En el pwd.
// 3. Asumiendo que se trata de una ruta absoluta.
// */