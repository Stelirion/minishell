/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:20:27 by mbrement          #+#    #+#             */
/*   Updated: 2022/11/10 12:36:42 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = -1;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while (++i < n)
		if ((s1[i] - s2[i]) != 0)
			return (s1[i] - s2[i]);
	return (0);
}
