// De env_init.c

// OLD
// /* Esta función se llama si envp o envp[0] son NULL
// En este caso, creamos la lista de variables del entorno con solo SHLVL=1 */
// // TO-DO: Test si esto es lo mismo que hacer env_new_variable("SHLVL", "1", env);
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

// OLD
// /* Crea la lista de variables de entorno a partir de **envp y devuelve el 
// puntero al head de la lista */
// static t_env	*env_copy_envp(char **envp)
// {
// 	t_env	*node;
// 	t_env	*head;
// 	t_env	*prev;
// 	int	i;

// 	i = 0;
// 	prev = NULL;
// 	while (envp[i])
// 	{
// 		node = env_init_node();
// 		if (!node)
// 			exit(EXIT_FAILURE);
// 		if (i == 0)
// 			head = node;
// 		if (env_get_envp_content(envp[i], node))
// 			exit(EXIT_FAILURE);
// 		env_add_node(&prev, node);
// 		i++;
// 	}
// 	return (head);
// }


// OLD
// /* Extrae el contenido de una linea de **envp y lo formatea de forma correcta
// para meterlo en un nodo de la lista de variables de entorno. */
// static int	env_get_envp_content(char *env_line, t_env *env)
// {
// 	int	eq_i;

// 	eq_i = ft_strchr_i(env_line, '=');
// 	if (eq_i == -1)
// 	{
// 		write(1, "STRCHR_I ERROR\n", 16); // Esto en principio no pasará nunca
// 		exit(EXIT_FAILURE);
// 	}
// 	env->name = ft_substr(env_line, 0, eq_i);
// 	if (!env->name)
// 	{
// 		ms_error(MALLOC_ERR);
// 		return (1);
// 	}
// 	env->content = ft_substr(env_line, eq_i + 1, ft_strlen(env_line) - eq_i);
// 	if (!env->content)
// 	{
// 		ms_error(MALLOC_ERR);
// 		free(env->name);
// 		return (1);
// 	}
// 	return (0);
// }

// OLD
// /* Actualiza el valor de la variable del entorno SHLVL
// Si SHLVL no existe en nuestra lista, la crea y le da el valor SHLVL=1
// Si SHLVL sí existe, le da el valor SHLVL+1. Si SHLVL >= 1000, vuelve a
// setear la variable a SHLVL=1 y printea un mensaje de warning.

// Esta función no retorna nada por que todos los errores llevan a exit(EXIT_FAILURE) */
// static t_env	*env_update_shlvl(t_env *env)
// {
// 	t_env	*node;
// 	int		shlvl;

// 	node = env_find("SHLVL", env);
// 	if (!node)
// 	{
// 		env_add("SHLVL", "1", &env);
// 		return (env);
// 	}
// 	shlvl = ft_atoi(node->content) + 1;
// 	free(node->content);
// 	if (shlvl >= 1000)
// 	{
// 		printf(SHLVL_WARNING, shlvl);
// 		shlvl = 1;
// 	}
// 	node->content = ft_itoa(shlvl);
// 	if (!node->content)
// 	{
// 		ms_error(MALLOC_ERR);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (env);
// }

// OLDER
// /* Busca la variable de entorno SHLVL en nuestra lista.
// Si no la encuentra, la crea y le da el valor SHLVL=1.
// Si la encuentra, le da el valor SHLVL + 1 excepto si SHLVL + 1 >= 1000.
// En ese caso, printea un warning y resetea su valor a SHLVL=1 */
// int	env_update_shlvl(t_env *env)
// {
// 	int	shlvl;

// 	shlvl = ft_atoi(env->content);
// 	free(env->content);
// 	if (shlvl + 1 >= 1000)
// 	{
// 		// Esto habrá que adaptarlo a nuestro formato de error si queremos ser pulcros
// 		printf(SHLVL_WARNING, shlvl + 1);
// 		env->content = ft_itoa(1);
// 		if (!env->content)
// 		{
// 			ms_error(MALLOC_ERR);
// 			return (1);
// 		}
// 		return (0);
// 	}
// 	env->content = ft_itoa(shlvl + 1);
// 	if (!env->content)
// 	{
// 		ms_error(MALLOC_ERR);
// 		return (1);
// 	}
// 	printf("%s=%s\n", env->name, env->content);
// 	return (0);
// }

////////////////////

// de env_list_tools.c

// int	env_add(char *name, char *content, t_env **head)
// {
// 	t_env	*new;
// 	t_env	*current;

// 	new = env_add_content(name, content);
// 	if (!new)
// 		return (1);
// 	new->prev = NULL;
// 	new->next = NULL;
// 	if (*head == NULL)
// 		*head = new;
// 	else
// 	{
// 		current = *head;
// 		while (current->next)
// 			current = current->next;
// 		current->next = new;
// 		new->prev = current;
// 	}
// 	return (0);
// }

// /* Añade un nodo en nuestra lista de variables de entorno y le da los valores 
// para ->name y ->content que recibe por sus argumentos. */
// int	env_new_variable(char *name, char *content, t_env *env)
// {
// 	t_env	*new;

// 	new = env_init_node();
// 	env_new(&env);
// 	if (!new)
// 		return (1);
// 	if (env_add_content(name, content, new))
// 	{
// 		free(new);
// 		return (1);
// 	}
// 	printf("new->name = %s\nnew->content = %s\n", new->name, new->content);
// 	env_append(&env, new);
// 	return (0);
// }

// OLD
/* Mete en la variable de entorno de la lista los valores de name y content */
// t_env	*env_add_content(char *name, char *content)
// {
// 	t_env	*new;

// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 	{
// 		ms_error(MALLOC_ERR);
// 		return (NULL);
// 	}
// 	if (name)
// 	{
// 		new->name = ft_strdup(name);
// 		if (!new->name)
// 		{
// 			ms_error(MALLOC_ERR);
// 			free(new);
// 			return (NULL);
// 		}
// 	}
// 	if (content)
// 	{
// 		new->content = ft_strdup(content);
// 		if (!new->content)
// 		{
// 			ms_error(MALLOC_ERR);
// 			free(new->name);
// 			free(new);
// 			return (NULL);
// 		}
// 	}
// 	return (new);
// }

// OLD
// /* Crea un nuevo nodo de la lista de variables de entorno e inicializa sus
// valores a NULL */
// t_env	*env_init_node(void)
// {
// 	t_env	*new;

// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 	{
// 		ms_error(MALLOC_ERR);
// 		return (NULL);
// 	}
// 	new->name = NULL;
// 	new->content = NULL;
// 	new->next = NULL;
// 	new->prev = NULL;
// 	return (new);
// }

// OLD
// /* Conecta un nuevo nodo al final de la lista de variables de entorno */
// // Es posible que esta variable se pueda convertir a void* casteando t_list
// void	env_append(t_env **head, t_env *new)
// {
// 	t_env	*last;

// 	if (!*head) // new es el primer nodo
// 		*head = new;
// 	if (*head == new)
// 		return ;
// 	check();
// 	last = tail(head);
// 	last->next = new;
// 	new->prev = last;
// 	return ;
// }

// OLD
// /* Añade un nodo a la lista de variables de entorno */
// void	env_add_node(t_env **tail, t_env *new)
// {
// 	if (*tail == NULL)
// 		*tail = new;
// 	else
// 	{
// 		new->prev = *tail;
// 		(*tail)->next = new;
// 		*tail = new;
// 	}
// }