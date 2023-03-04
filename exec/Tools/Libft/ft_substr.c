/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:07:21 by mbrement          #+#    #+#             */
/*   Updated: 2022/11/14 18:47:41 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*str;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (i <= start)
	{
		str = (char *)malloc (sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	else if (i - start > len)
		str = (char *)malloc((char)len + 1);
	else
		str = (char *)malloc(i - start + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s[start + ++i] && i < len)
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}
