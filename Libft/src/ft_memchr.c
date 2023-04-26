/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:56:01 by mbrement          #+#    #+#             */
/*   Updated: 2022/11/10 12:41:38 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	chr;
	unsigned char	*s;

	i = -1;
	chr = c;
	s = (unsigned char *)str;
	while (++i < n)
		if (s[i] == chr)
			return ((void *)str + i);
	return (NULL);
}
