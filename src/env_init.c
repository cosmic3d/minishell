/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:08:12 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/11 17:31:01 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		env_null_case(void);
static t_env	*env_copy_envp(char **envp);
static void		env_update_shlvl(t_env *env);
static int		env_get_content(char *env_line, t_env *env);

/* Esta función inicializa la lista de variables del entorno en base a **envp
que recibe minishell en el main.
El recorrido de esta función contempla tres posibilidades:
- envp o envp[0] == NULL
- envp no contiene SHLVL
- envp sí contiene SHLVL */
void	env_init(t_ms *ms, char **envp)
{
	t_env	*env;

	env = NULL;
	if (!envp || !envp[0]) // NULL case
	{
		env_add("SHLVL", "1", env);
		// env_null_case(env);
		return ;
	}
	env_copy_envp(&env, envp);
	env_update_shlvl(env);
	ms->env = env;
	return ;
}

// /* Esta función se llama si envp o envp[0] son NULL
// En este caso, creamos la lista de variables del entorno con solo SHLVL=1 */
// // TO-DO: Test si esto es lo mismo que hacer env_add("SHLVL", "1", env);
// static int	env_null_case(t_env *env)
// {	
// 	env = env_new_node();
// 	if (!env)
// 		exit(NULL);
// 	env->name = ft_strdup("SHLVL");
// 	if (!env->name)
// 	{
// 		ms_error(MALLOC_ERR);
// 		free(env);
// 		return (1);
// 	}
// 	env->content = ft_strdup("1");
// 	if (!env->content)
// 	{
// 		ms_error(MALLOC_ERR);
// 		free(env->name);
// 		free(env);
// 		return (1);
// 	}
// 	return (0);
// }



/* Crea la lista de variables de entorno a partir de **envp y devuelve el 
puntero al head de la lista */
static void	env_copy_envp(t_env *head, char **envp)
{
	t_env	*node;
	int	i;

	i = 0;
	while (envp[i])
	{
		node = env_new_node();
		if (!node)
			exit(EXIT_FAILURE);
		if (i == 0)
			head = node;
		if (env_get_content(envp[i], node))
			exit(EXIT_FAILURE);
		env_append(head, node);
		i++;
	}
}

/* Conecta un nuevo nodo al final de la lista de variables de entorno */
// Es posible que esta variable se pueda convertir a void* casteando t_list
void	env_append(t_env *head, t_env *new)
{
	t_env	*last;

	if (head == new)
		return ;
	last = tail(*head);
	last->next = new;
	new->prev = last;
	return ;
}

/* Extrae el contenido de una linea de **envp y lo formatea de forma correcta
para meterlo en un nodo de la lista de variables de entorno. */
static int	env_get_content(char *env_line, t_env *env)
{
	int	eq_i;

	eq_i = ft_strchr_i(env_line, '=');
	if (eq_i == -1)
	{
		// Esto hopefully no tiene que ocurrir nunca, pero dejo este error de momento
		printf("Error inesperado, ft_strchr_i en envp_dup.c\n");
		exit(1);
	}
	env->name = ft_substr(env_line, 0, eq_i);
	if (!env->name)
	{
		ms_error(MALLOC_ERR);
		return (1);
	}
	env->content = ft_substr(env_line, eq_i + 1, ft_strlen(env_line) - eq_i);
	if (!env->content)
	{
		ms_error(MALLOC_ERR);
		free(env->name);
		return (1);
	}
	return (0);
}


/* Actualiza el valor de la variable del entorno SHLVL
Si SHLVL no existe en nuestra lista, la crea y le da el valor SHLVL=1
Si SHLVL sí existe, le da el valor SHLVL+1. Si SHLVL >= 1000, vuelve a
setear la variable a SHLVL=1 y printea un mensaje de warning.

Esta función no retorna nada por que todos los errores llevan a exit(1) */
static void	env_update_shlvl(t_env *env)
{
	t_env	*node;
	int		shlvl;

	node = env_find("SHLVL", env);
	if (!node)
	{
		env_add("SHLVL", "1", env);
		return ;
	}
	shlvl = ft_atoi(node->content) + 1;
	free(node->content);
	if (shlvl >= 1000)
	{
		printf(SHLVL_WARNING, shlvl);
		shlvl = 1;
	}
	node->content = ft_itoa(shlvl);
	if (!node->content)
	{
		ms_error(MALLOC_ERR);
		exit(EXIT_FAILURE);
	}
	return ;
}

/* Busca la variable de entorno SHLVL en nuestra lista.
Si no la encuentra, la crea y le da el valor SHLVL=1.
Si la encuentra, le da el valor SHLVL + 1 excepto si SHLVL + 1 >= 1000.
En ese caso, printea un warning y resetea su valor a SHLVL=1 */
int	env_update_shlvl(t_env *env)
{
	int	shlvl;

	shlvl = ft_atoi(env->content);
	free(env->content);
	if (shlvl + 1 >= 1000)
	{
		// Esto habrá que adaptarlo a nuestro formato de error si queremos ser pulcros
		printf(SHLVL_WARNING, shlvl + 1);
		env->content = ft_itoa(1);
		if (!env->content)
		{
			ms_error(MALLOC_ERR);
			return (1);
		}
		return (0);
	}
	env->content = ft_itoa(shlvl + 1);
	if (!env->content)
	{
		ms_error(MALLOC_ERR);
		return (1);
	}
	printf("%s=%s\n", env->name, env->content);
	return (0);
}
