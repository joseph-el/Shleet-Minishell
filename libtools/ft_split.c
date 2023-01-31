/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:20:12 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/24 19:02:59 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools.h"

static char	**clear_memory(char **error, int place)
{
	int	index;

	index = 0;
	while (index < place)
		free(error[index++]);
	free(error);
	return (NULL);
}

static int	count_words(char const *str, char c)
{
	int	words;

	words = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str != c && *str)
		{
			while (*str != c && *str)
				str++;
			words++;
		}
	}
	return (words);
}

static char	**build_arrays(char **str, char const *s, int c, int save)
{
	int	index;
	int	place;

	index = 0;
	place = 0;
	while (s[place])
	{
		if (s[place] == c)
		{
			place++;
			continue ;
		}
		save = place;
		while (s[place] && s[place] != c)
			place++;
			str[index] = malloc(sizeof(char) * (place - save + 1));
		if (! str[index])
			return (clear_memory(str, index));
		ft_strlcpy(str[index], s + save, place - save + 1);
		index++;
	}
	str[index] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		save;

	save = 0;
	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!str)
		return (NULL);
	build_arrays(str, s, c, save);
	return (str);
}
