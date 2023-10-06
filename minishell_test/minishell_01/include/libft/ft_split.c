/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apresas- <apresas-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:24:39 by apresas-          #+#    #+#             */
/*   Updated: 2023/02/08 12:19:12 by apresas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i] != '\0')
			{
				i++;
			}
			count++;
		}
	}
	return (count);
}

static char	**free_all(char **array, int k)
{
	while (k > 0)
		free(array[k--]);
	free(array[k]);
	free(array);
	return (NULL);
}

static char	**place_words(const char *s, char **array, char c, int words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (k < words)
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i] != c && s[i] != '\0')
			{
				i++;
				j++;
			}
			array[k] = ft_calloc (sizeof(char), (j + 1));
			if (!array)
				return (free_all(array, k));
			ft_strlcpy(array[k], &s[i - j], j + 1);
			k++;
		}
		i++;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		words;

	if (!s)
		return (0);
	words = count_words(s, c);
	array = malloc (sizeof(char *) * (words + 1));
	if (!array)
		return (0);
	place_words(s, array, c, words);
	array[words] = 0;
	return (array);
}
