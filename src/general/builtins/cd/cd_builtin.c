/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:02:32 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/27 15:12:55 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg_errors(char *arg);
static void	cd_error(char *arg, char *error_str);

int	ms_cd(t_ms *ms, char **argv)
{
	char	*error_str;
	char	*oldpwd;
	char	*pwd;

	if (argv[1] == NULL | !argv[1][0])
		return (EXIT_SUCCESS);
	if (check_arg_errors(argv[1]) == FAILURE)
		return (EXIT_FAILURE);
	if (chdir(argv[1]) == -1)
	{
		perror("Testing chdir");
		return(EXIT_FAILURE);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		cd_error(argv[1], "getcwd error noseque"); // Hay que pensar esto
		return (EXIT_FAILURE);
	}
	update_environment();
	env_update("PWD", new_pwd, ms->env);
	return (EXIT_SUCCESS);
}

int	update_environment(t_ms *ms)
{
	/* Primero updateamos OLDPWD
	OLDPWD="$PWD"*/
	t_env *oldpwd;

	oldpwd = env_find("OLDPWD", ms->env);
	if (!oldpwd)
	{
		if (env_add("OLDPWD", , &ms->env))
	}
}

static int	check_arg_errors(char *arg)
{
	struct stat file;

	if (access(arg, FILE_EXISTS) == FAILURE)
	{
		cd_error(arg, NO_SUCH_FILE);
		return (FAILURE);
	}
	lstat(arg, &file);
	if (!S_ISDIR(file.st_mode))
	{
		cd_error(arg, NOT_DIR);
		return (FAILURE);
	}
	if (access(arg, HAS_EXECUTE_PERMISSIONS) == FAILURE)
	{
		cd_error(arg, PERM_DENIED);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	cd_error(char *arg, char *error_str)
{
	write(2, "minishell: cd: ", 15);
	write(2, &arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, &error_str, ft_strlen(error_str));
	write(2, "\n");
}

/* Sobre cd

Funcionalidades a implementar:

cd <relative_path>
cd <absolute_path>

Funcionalidades innecesarias:

cd - => cd al anterior directorio
cd ~ => cd a home
cd => cd a home

Hay que debatir si hacen falta ms->pwd y ms->oldpwd

Sobre env_update, si la variable no existe, devuelve 1 y no hace nada.

*/


/* Caso curioso que me he encontrado:

cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
bash-3.2$

Esto me ocurrió haciendo cd . estando en un directorio que había borrado
*/