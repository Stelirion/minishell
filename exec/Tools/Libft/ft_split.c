/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:58:58 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/03 15:29:37 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	index;
	size_t	cut;

	if (!s)
		return (NULL);
	cut = ft_cutter(s, c);
	dst = (char **)malloc(sizeof(char *) * (cut + 1));
	if (!dst)
		return (NULL);
	index = 0;
	while (cut > index)
	{
		dst[index] = ft_spliter(s, index, c);
		if (!dst[index])
		{
			dst = ft_free_split(dst, index);
			return (NULL);
		}
		index++;
	}
	dst[cut] = NULL;
	return (dst);
}
