/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:00:26 by mbrement          #+#    #+#             */
/*   Updated: 2022/11/11 15:41:44 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{	
	size_t	i;
	char	*swap;
	char	*conv;

	i = -1;
	conv = dst;
	swap = (char *)src;
	if (!src && !dst)
		return (dst);
	while (++i < n)
		conv[i] = swap[i];
	return (dst);
}
