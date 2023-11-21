/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:02:32 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/21 15:48:00 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd(t_ms *ms, char **argv)
{
	char	*new_oldpwd;
	char	*new_pwd;

	if (argv[1] == NULL)
		return (EXIT_SUCCESS);
	else if (!argv[1][0])
		return (EXIT_SUCCESS);
	new_oldpwd = get_env_content("OLDPWD", ms->env); // debatir sobre el error, get_env_content si falla por malloc hace quit y fuera, pero no dirá nada de minishell: cd: tal
	env_update("OLDPWD", new_oldpwd, ms->env);
	if (chdir(argv[1]) == -1)
	{
		// "minishell: cd: <argumento>: "
		perror(NULL);
		return(EXIT_FAILURE);
	}
	new_pwd = getcwd(NULL, 0);
	env_update("PWD", new_pwd, ms->env);
	return (EXIT_SUCCESS);
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