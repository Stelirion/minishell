/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:05:08 by mbrement          #+#    #+#             */
/*   Updated: 2022/11/13 17:50:14 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	reach;
	size_t	len_hay;

	i = -1;
	if (!haystack && !len)
		return (NULL);
	len_hay = ft_strlen(haystack);
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[++i] && i <= len)
	{
		reach = 0;
		if (haystack[i] == needle[reach])
		{
			while (haystack[i + reach] == needle[reach]
				&& (reach + i) <= len && (reach + i <= len_hay))
			{
				reach++;
				if (reach == ft_strlen(needle) && reach + i <= len)
					return ((char *)haystack + i);
			}
		}
	}
	return (NULL);
}
