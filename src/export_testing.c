/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_testing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:33:07 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/17 18:47:25 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TO-DO : 
*/ 

/* Función recursiva que printea las variables de entorno en el formato que 
utiliza el builtin 'export' 
Para que funcione correctamente se tiene que llamar así:
export_print(env, env, NULL, NULL); */
int	export_print(t_env *env, t_env *current, t_env *abc_min, char *prev)
{
	if (!env)
		return (FAILURE);
	while (current)
	{
		if (!prev || ft_strlcmp(current->name, prev) < 0)
		{
			if (!abc_min || ft_strlcmp(current->name, abc_min->name) > 0)
				abc_min = current;
		}
		current = current->next;
	}
	if (abc_min)
	{
		export_print(env, env, NULL, abc_min->name);
		if (!ft_strcmp(abc_min->name, "_"))
			return (SUCCESS);
		printf("declare -x %s=", abc_min->name);
		if (abc_min->content)
			printf("\"%s\"", abc_min->content);
		printf("\n");
	}
	return (SUCCESS);
}

// Esta función es el núncleo del builtin 'export'
int	ms_export(t_ms *ms, char **argv)
{
	int	err_no;
	int	i;
	int	valid_input;

	i = 0;
	valid_input = 0;
	while (argv[i])
	{
		if (export_syntax_check(argv[i]))
			valid_input++;
		i++;
	}
	if (!valid_input)
		export_print(ms->env, ms->env, NULL, NULL);

}

int	export_syntax_check(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && (arg[i] != '=' && arg[i] != ' '))
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			flags == 1;
	}
	
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	
	if ()
	
	while (arg[i])
	{
		
	}
}
