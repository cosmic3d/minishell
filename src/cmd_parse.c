/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:06:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/10/11 21:14:58 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

static char	**ft_free(char **array, int k)
{
	while (k > 0)
		free(array[k--]);
	free(array[k]);
	free(array);
	return (NULL);
}

int	valid_brackets(char *str)
{
	int	i;
	int	two_simple;
	int	two_double;

	i = -1;
	two_double = 1;
	two_simple = 1;
	while (str[++i])
	{
		if (str[i] == '\'')
			two_simple *= -1;
		else if (str[i] == '\"')
			two_double *= -1;
	}
	if (two_double == -1 || two_simple == -1)
		return (0);
	return (1);
}

static int	word_count_sh(char *str, char separator)
{
	int	i;
	int	counter;
	int	in_bracks;

	counter = 0;
	i = -1;
	in_bracks = 0;
	while (str[++i] != '\0')
	{
		if (!in_bracks && (str[i] == '\'' || str[i] == '\"'))
		{
			in_bracks = 1;
			counter++;
			continue ;
		}
		if (in_bracks && (str[i] != '\'' || str[i] != '\"'))
			continue ;
		else if (in_bracks)
			in_bracks = 0;
		if ((str[i] == separator && str[i + 1] != separator \
		&& str[i + 1] && !in_bracks) || (str[i] != separator && i == 0))
			counter++;
	}
	return (counter);
}

static char	**loc_mem_sh(char *str, char s, int wordc)
{
	int		i;
	int		j;
	int		w;
	char	**words;
	int		in_bracks;

	words = malloc(sizeof(char *) * (wordc + 1));
	if (!words)
		return (0);
	j = 0;
	i = -1;
	in_bracks = -1;
	while (++i < wordc)
	{
		w = 0;
		if (str[i] == '\'' || str[i] == '\"')
			in_bracks *= -1;
		while ((str[j] == s && !w) || (str[j] && ++w))
			j++;
		words[i] = malloc(sizeof(char) * (w + 1));
		if (!words[i])
			return (ft_free(words, i));
	}
	return (words);
}

char	**ft_split_ms(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**words;

	words = loc_mem_sh((char *)s, c, word_count_sh((char *)s, c));
	if (!words)
		return (0);
	i = -1;
	j = 0;
	while (++i < word_count_sh((char *)s, c))
	{
		k = 0;
		while ((char)s[j] == c)
			j++;
		if ((j == 0 && (char)s[j] != c) || ((char)s[j] != c && (char)s[j]))
		{
			while ((char)s[j] && (char)s[j] != c)
				words[i][k++] = (char)s[j++];
			words[i][k] = '\0';
		}
	}
	words[i] = NULL;
	return (words);
}

int	main(void)
{
	int		i;
	char	**test;

	test = ft_split_ms("Hola como estas", ' ');
	i = -1;
	while (test[++i])
		printf("%s\n", test[i]);
	exit(1);
}
