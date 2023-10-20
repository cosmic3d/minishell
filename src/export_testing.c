/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_testing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:33:07 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/20 18:07:32 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_print(t_env *env, t_env *node, t_env *abc_min, char *prev);
static int	export_process_argument(t_export *data, char *arg, t_env *env);
static int	export_split_arg(t_export *data, char *arg);
static int	export_new_content(t_export *data, t_env *node);
static int	export_add_content(t_export *data, t_env *node);
void	export_print_errors(t_export *data, char **argv);

/* Funcionamiento de export:
Export retornará 1 si una de las variables que intente crear no es válida.
También printeará un mensaje de error por cada variable que no sea válida.
Pero, de todas formas, aunque retorne 1 y haya variables no válidas, si
en los argumentos alguna de las variables sí es válida, esa la asignará
correctamente.
*/

/* TO DO!!

	- Decidir si export tiene que hacer una excepción con $_ o no.
	- 

*/

// Esta función es el núncleo del builtin 'export'
int	ms_export(t_ms *ms, char **argv)
{
	t_export	data;
	int 		i;
	
	i = 1;
	data.exit_status = EXIT_SUCCESS;
	if (!argv[i])
		return (export_print(ms->env, ms->env, NULL, NULL)); // maybe
	while (argv[i])
	{
		export_init(&data, argv[i]);
		if (!data.valid_name)
			export_perror(argv[i]);
		if (export_process_argument(&data, argv[i], ms->env))
		{
// Este error es por malloc, como tenemos t_ms *ms, podriamos usar exit(1) y fuera?
			return (FAILURE);
		}
		
		i++;
	}
	return (data.exit_status);
}

/* Función recursiva que printea las variables de entorno en el formato que 
utiliza el builtin 'export' 
Para que funcione correctamente se tiene que llamar así:
export_print(env, env, NULL, NULL);
Siempre retorna success por que aunque no haya variables de entorno, export
no lo considera un error de ningun tipo. */
static int	export_print(t_env *env, t_env *node, t_env *abc_min, char *prev)
{
	if (!env)
		return (SUCCESS);
	while (node)
	{
		if (!prev || ft_strlcmp(node->name, prev) < 0)
		{
			if (!abc_min || ft_strlcmp(node->name, abc_min->name) > 0)
				abc_min = node;
		}
		node = node->next;
	}
	if (abc_min)
	{
		export_print(env, env, NULL, abc_min->name);
		if (!ft_strcmp(abc_min->name, "_"))
			return (SUCCESS);
		printf("declare -x %s", abc_min->name);
		if (abc_min->content)
			printf("=\"%s\"", abc_min->content);
		printf("\n");
	}
	return (SUCCESS);
}

static int	export_process_argument(t_export *data, char *arg, t_env *env)
{
	t_env	*new;

	if (!data->valid_name)
		return (SUCCESS);
	if (export_split_arg(data, arg))
		return (FAILURE);
	new = env_find(data->name, env);
	if (new)
	{
		if (export_new_content(data, new))
			return (FAILURE);
	}
	else
	{
		if (env_add(data->name, data->content, &env))
			return (FAILURE);
	}
	if (!data->valid_name)
		data->exit_status = 1;
	free(data->name);
	free(data->content);
	return (SUCCESS);
}

static int	export_split_arg(t_export *data, char *arg)
{
	data->name = ft_substr(arg, 0, data->name_len);
	if (!data->name)
	{
		ms_error(MALLOC_ERR);
		return (FAILURE);
	}
	if (!data->valid_content)
		return (SUCCESS);
	data->content = ft_strdup(arg + data->eq_i + 1);
	if (!data->content)
	{
		ms_error(MALLOC_ERR);
		free(data->name);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	export_new_content(t_export *data, t_env *node)
{
	if (data->op == EXPORT_NO_OP && !data->content)
		return (SUCCESS);
	if (data->op == EXPORT_NO_OP || data->op == EXPORT_EQ)
	{
		if (env_update(data->name, data->content, node))
		{
			ms_error(MALLOC_ERR);
			free(data->name);
			free(data->content);
			return (FAILURE);
		}
	}
	else if (data->op == EXPORT_ADD)
	{
		if (export_add_content(data, node))
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	export_add_content(t_export *data, t_env *node)
{
	char	*old_content;
	char	*new_content;

	if (data->op != EXPORT_ADD)
		return (SUCCESS);
	old_content = node->content;
	new_content = ft_strjoin(old_content, data->content);
	if (!new_content)
	{
		ms_error(MALLOC_ERR);
		free(data->name);
		free(data->content);
		return (FAILURE);
	}
	node->content = new_content;
	free(old_content);
	return (SUCCESS);
}
