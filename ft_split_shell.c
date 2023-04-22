/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:24:59 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/22 15:38:06 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_spliter(char const *s, int index, char c)
{
	int		i;
	int		j;
	int		result;

	i = 0;
	j = 0;
	result = -1;
	while (s[i] && result != index)
	{
		if (s[i] != c)
		{
			result++;
			if (i != 0 && s[i - 1] != c)
				result--;
		}
		i++;
	}
	if (i > 0)
		i--;
	while (s[i + j] && s[i + j] != c)
		j++;
	return (ft_substr(s, i, j));
}

static int	ft_cutter(char const *s, char c)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			result++;
			if (i != 0 && s[i - 1] != c)
				result--;
		}
		i++;
	}
	return (result);
}

static char	**ft_free_split(char **dst, int index)
{
	while (index >= 0)
	{
		free(dst[index]);
		index--;
	}
	free(dst);
	return (0);
}

char	*before(const char *s)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = -1;
	j = 0;
	while (s[++i] != '\0')
		if (s[i] == '"')
			j++;
	if (j % 2 != 0)
		return (NULL);
	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) - j + 1));
	while (s[i + j] && s[i + j] != '\0')
	{
		if (str[i + j] != '"')
			str[i] = s[i + j];
		else
			j++;
		if (str[i + j])
			i++;
	}
	str[i + j] = '\0';
	return (str);
}

char	**ft_split_shell(char const *s)
{
	char	**dst;
	size_t	index;
	size_t	cut;
	char	*str;

	if (!s)
		return (NULL);
	str = before(s);
	if (!str)
		return (NULL);
	cut = ft_cutter(str, ' ');
	dst = (char **)malloc(sizeof(char *) * (cut + 1));
	if (!dst)
		return (NULL);
	index = 0;
	while (cut > index)
	{
		dst[index] = ft_spliter(str, index, ' ');
		if (!dst[index])
			return (dst = ft_free_split(dst, index), NULL);
		index++;
	}
	dst[cut] = NULL;
	return (free(str), dst);
}
