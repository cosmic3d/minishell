/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:27:13 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/11 17:34:01 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Añade un nodo en nuestra lista de variables de entorno y le da los valores 
para ->name y ->content que recibe por sus argumentos. */
int	env_new_environment_variable(char *name, char *content, t_env *env)
{
	t_env	*new;

	new = env_new_node();
	if (!new)
		return (1);
	if (env_add_content(name, content, new))
	{
		free(new);
		return (1);
	}
	env_append()
	return (0);
}

/* Mete en la variable de entorno de la lista los valores de name y content */
int	env_add_content(char *name, char *content, t_env *env)
{
	env->name = ft_strdup(name);
	if (!env->name)
	{
		ms_error(MALLOC_ERR);
		free(env);
		return (1);
	}
	env->content = ft_strdup(content);
	if (!env->content)
	{
		ms_error(MALLOC_ERR);
		free(env->name);
		free(env);
		return (1);
	}
	return (0);
}

/* Crea un nuevo nodo de la lista de variables de entorno e inicializa sus
valores a NULL */
t_env	*env_init_node(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		ms_error(MALLOC_ERR);
		return (NULL);
	}
	new->name = NULL;
	new->content = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/* Añade un nodo a la lista de variables de entorno */
void	env_add_node(t_env **tail, t_env *new)
{
	if (*tail == NULL)
		*tail = new;
	else
	{
		new->prev = *tail;
		(*tail)->next = new;
		*tail = new;
	}
}

/* Recorre la lista de variable de entorno y busca una en particular por 
el valor de su ->name, cuando la encuentra, devuelve el puntero a ese nodo.
Si no encuentra la variable de entorno, devuelve NULL */
t_env	*env_find(char *name, t_env *head)
{
	while (head)
	{
		if (!ft_strcmp(head->name, name))
		{
			return (head);
		}
		head = head->next;
	}
	return (NULL);
}

/* Elimina la variable de entorno con el name dado de la lista y 
reroutea sus nodos previos y siguientes para unir la lista. 
Luego, libera el contenido y el puntero de este nodo. 
Si en la lista no hay variable de entorno con este nombre, retorna 1. */
int	env_remove(char *name, t_env *env)
{
	t_env	*remove;

	remove = env_find(name, env);
	if (!remove)
		return (1); // Environment Variable doesn't exist
	if (remove->prev)
		remove->prev->next = remove->next;
	if (remove->next)
		remove->next->prev = remove->prev;
	free(remove->name);
	free(remove->content);
	free(remove);
	return (0);	
}

/* Busca la variable de entorno en base a su ->name y actualiza su content. */
int	env_update(char *name, char *content, t_env *env)
{
	t_env	*change;

	change = env_find(name, env);
	if (!change)
	{
		// Variable de entorno no encontrada.
		// Podríamos llamar aquí a que sea creada y añadida o hacerlo
		// fuera de la función donde sea llamada por export
		return (1);
	}
	free(change->content);
	change->content = ft_strdup(content);
	if (!change->content)
	{
		ms_error(MALLOC_ERR);
		return (1);
	}
	return (0);
}

/* Printea la lista de variables del entorno.
La variable function puede ser ENV o EXPORT que son las dos funciiones que 
pueden printear la lista de variables de entorno.
En base al valor de function, este programa imprimirá en un formato u otro. */
int	env_print(t_env *env, int function)
{
	if (function == ENV)
	{
		while (env)
		{
			if (env->content)
				printf("%s=%s\n", env->name, env->content);
			env = env->next;
		}
	}
	else if (function == EXPORT)
	{
		while (env)
		{
			printf("declare -x %s", env->name);
			if (env->content)
				printf("=\"%s\"", env->content);
			printf("\n");
			env = env->next;
		}
	}
	return (0);
}

/* TO-DO:

*/