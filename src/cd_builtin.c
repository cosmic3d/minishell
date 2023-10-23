/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:02:32 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/23 13:32:39 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd(t_ms *ms, char **argv)
{
	if (argv[2] != NULL)
	{
		write(2, "minishell: cd: too many arguments", 34);
		return (EXIT_FAILURE);
	}
	if (!ft_strncmp(argv[1], "~", 1))
		cd_home(ms->env);
	
}

int	cd_home(t_env *env)
{
	t_env	*home_env;
	char	*home;

	home_env = env_find("HOME", env);
	if (!home_env)
}

// Sobre cd ~
/*
En bash, aunque hagas unset de $HOME, cd ~ sigue funcionando.
Aquí no, habría que decidir qué hacer respecto a esto.

Puede que usar chdir("~"); sea suficiente.

podemos también recibir cosas como ~/tal/cual
Pero no tenemos por qué gestionar estos casos por que no son paths relativas ni absolutas, usan ~ y eso es una variable interna, no lo contaría como una dirección válida.
A no ser que chdir lo gestione solo.
*/

