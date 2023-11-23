/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:24:39 by apresas-          #+#    #+#             */
/*   Updated: 2023/11/23 18:31:57 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **str, int wordc)
{
	int	i;

	i = 0;
	while (i < wordc)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static int	word_count(char *str, char separator)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != separator && i == 0)
			counter++;
		if (str[i] == separator && str[i + 1] != separator && str[i + 1])
			counter++;
		i++;
	}
	return (counter);
}

static char	**loc_mem(char *str, char s)
{
	int		i;
	int		j;
	int		w;
	int		wordc;
	char	**words;

	wordc = word_count(str, s);
	words = malloc(sizeof(char *) * (wordc + 1));
	if (!words)
		return (0);
	j = 0;
	i = -1;
	while (++i < wordc)
	{
		w = 0;
		while (str[j] == s)
			j++;
		while ((str[j] && str[j] != s)
			&& ((j == 0 && str[j] != s) || (str[j] != s)) && w++ != -1)
			j++;
		words[i] = malloc(sizeof(char) * (w + 1));
		if (!words[i])
			return (ft_free(words, i));
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**words;

	words = loc_mem((char *)s, c);
	if (!words)
		return (0);
	i = 0;
	j = 0;
	while (i < word_count((char *)s, c))
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
		i++;
	}
	words[i] = NULL;
	return (words);
}
