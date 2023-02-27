/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:37:07 by mbrement          #+#    #+#             */
/*   Updated: 2022/11/13 17:50:13 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	chr;

	chr = c;
	i = ft_strlen(s);
	if (c == '\0')
		return ((char *)s + i);
	while (s[i] >= 0)
	{
		if (s[i] == chr)
			return ((char *)s + i);
		if (i != 0)
			i--;
		else
			break ;
	}
	return (NULL);
}
