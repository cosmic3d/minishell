/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_testing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:33:07 by apresas-          #+#    #+#             */
/*   Updated: 2023/10/18 19:36:30 by apresas-         ###   ########.fr       */
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

/* Funcionamiento de export:
Export retornará 1 si una de las variables que intente crear no es válida.
También printeará un mensaje de error por cada variable que no sea válida.
Pero, de todas formas, aunque retorne 1 y haya variables no válidas, si
en los argumentos alguna de las variables sí es válida, esa la asignará
correctamente.
*/

// Esta función es el núncleo del builtin 'export'
int	ms_export(t_ms *ms, char **argv)
{
	int	err_no;
	int	i;
	int	valid_input;

	i = 0;
	valid_input = 0;
	if (!argv)
		export_print(ms->env, ms->env, NULL, NULL);
	while (argv[i])
	{
		if (export_syntax_check(argv[i]))
			printf("INVALID NAME"); // Hay que ver cómo gestionar esto
		i++;
	}
	if (!valid_input)
		export_print(ms->env, ms->env, NULL, NULL);
}



/* VALORES FLAG:

1 = Characteres inválidos en el Identifier, o sea el Nombre de la variable.
	Formato del error: (COMPROBAR EN LOS MACS DE 42)
		bash: export: `<argumento en questión>': not a valid identifier

*/

/* Qué hacer en export_syntax_check:

Voy a asumir que el parser me va a enviar los argumentos sin comillas de más

Posibles casos que reciba:
	Válidos:
		NOMBRE
		NOMBRE=
		NOMBRE=texto
	Inválidos
		<NOMBRE con carácteres inválidos> 
		<NOMBRE que empieza con un digito>

	Gestión de casos válidos:
		NOMBRE
			Añadimos una variable de entorno que solo tiene nombre.
		NOMBRE=
			Añadimos una variable de entorno que tiene nombre y contenido vacío
				NOMBRE=""
		NOMBRE=texto
			Añadimos una variable de entorno que tiene nombre y contenido
				NOMBRE="contenido"
*/

int	export_syntax_check(char *arg)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	// if (!arg) ? Creo que esto ya se habrá comprobaro antes de enviarlo aquí
	if (arg[0] == '\0' || ft_isdigit(arg[0]))
		return (FAILURE);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_match_ch(arg[i], EXPORT_NAME_PATTERN))
			return (FAILURE);
		i++;
	}
	// if (arg[i] == '=')
	// 	i++;
	// while (arg[i])
	// {
	// 	i++;
	// }
	return (SUCCESS);
}
